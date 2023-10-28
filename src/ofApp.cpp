#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    sqrtNumSplit = 32;               // 分割数の正の平方根
    numSplit = pow(sqrtNumSplit, 2); // 分割数
    numImg = 10;                     // 画像数
    minDOpacity = 0.01;              // 透明度の変化幅の最小値
    maxDOpacity = 0.03;              // 透明度の変化幅の最大値

    // bin/data/images/ フォルダ内のjpg画像を取得
    imagesDir.listDir("images");
    imagesDir.allowExt("jpg");

    // 指定した画像数より画像が少ない場合は最大数を取得する
    if (imagesDir.size() < numImg)
    {
        numImg = imagesDir.size();
    }

    // 画像ロード
    images.assign(numImg, ofImage());
    for (int i = 0; i < numImg; i++)
    {
        images[i].load(imagesDir.getPath(i));
    }

    init();
}

//--------------------------------------------------------------
void ofApp::init()
{
    // ウィンドウサイズを取得
    winW = ofGetWindowWidth();
    winH = ofGetWindowHeight();

    imgW = winW;
    imgH = winH;

    // 結合画像内の画像の行数,列数を計算
    imgCol = numImg * imgW < MAX_TEX_RES ? numImg : floor(MAX_TEX_RES / imgW);
    imgRow = ceil(numImg / float(imgCol));
    joinedTexW = imgW * imgCol;
    joinedTexH = imgH * imgRow;
    // 結合画像サイズが制限を超える場合は画像数を減らす
    if (MAX_TEX_RES < joinedTexH)
    {
        imgRow = floor(MAX_TEX_RES / imgH);
        joinedTexH = imgH * imgRow;
        numImg = imgCol * imgRow;
    }

    // 画像を一つの画像に結合
    joinedFbo.allocate(joinedTexW, joinedTexH, GL_RGB);
    joinedFbo.begin();
    for (int y = 0; y < imgRow; y++)
    {
        for (int x = 0; x < imgCol; x++)
        {
            int index = y * imgCol + x;
            if (index < numImg)
                images[index].draw(x * imgW, y * imgH, imgW, imgH);
        }
    }
    joinedFbo.end();

    // 空画像のメモリ確保
    emptyImage.allocate(winW, winH, OF_IMAGE_COLOR);

    // 描画シェーダーにデータを送信
    renderShader.load("shader/passthru.vert", "shader/render.frag");
    renderShader.begin();
    renderShader.setUniform1i("sqrtNumSplit", sqrtNumSplit);
    renderShader.setUniform1i("numSplit", numSplit);
    renderShader.setUniform1i("numImg", numImg);
    renderShader.setUniform1i("imgCol", imgCol);
    renderShader.setUniform2f("imgSize", imgW, imgH);
    renderShader.setUniform2f("winSize", winW, winH);
    renderShader.setUniformTexture("joinedTex", joinedFbo.getTexture(), 1);
    renderShader.end();

    // 分割領域のデータ作成
    vector<float> splitData(numSplit * 3);
    vector<float> dOpacityData(numSplit);
    for (int i = 0; i < numSplit; i++)
    {
        splitData[i * 3 + 0] = ofRandom(1.0);                 // 現在の画像ID
        splitData[i * 3 + 1] = ofRandom(1.0);                 // 次の画像ID
        splitData[i * 3 + 2] = 1.0f;                          // 透明度
        dOpacityData[i] = ofRandom(minDOpacity, maxDOpacity); // 透明度の変化幅
    }
    splitTex.allocate(sqrtNumSplit, sqrtNumSplit, GL_RGB);
    splitTex.src->getTexture().loadData(splitData.data(), sqrtNumSplit, sqrtNumSplit, GL_RGB);
    splitTex.dst->getTexture().loadData(splitData.data(), sqrtNumSplit, sqrtNumSplit, GL_RGB);
    dOpacityTex.loadData(dOpacityData.data(), sqrtNumSplit, sqrtNumSplit, GL_RED);

    // 分割領域のデータ更新シェーダーにデータ送信
    splitShader.load("shader/passthru.vert", "shader/update.frag");
    splitShader.begin();
    splitShader.setUniformTexture("dOpacityTex", dOpacityTex, 4);
    splitShader.end();
}

//--------------------------------------------------------------
void ofApp::update()
{
    //----------------------------------------------------------
    // 分割領域のデータ更新
    splitTex.dst->begin();
    ofClear(0);
    splitShader.begin();

    splitShader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    splitShader.setUniformTexture("preSplitTex", splitTex.src->getTexture(), 3);
    splitTex.src->draw(0, 0);

    splitShader.end();
    splitTex.dst->end();

    splitTex.swap();

    //----------------------------------------------------------
    // 描画シェーダーにデータを送信
    renderShader.begin();
    ofClear(0);
    renderShader.setUniformTexture("splitTex", splitTex.src->getTexture(), 2);
    renderShader.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // 空画像上に描画シェーダーのテクスチャを描画
    renderShader.begin();
    emptyImage.draw(0, 0, winW, winH);
    renderShader.end();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    init();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    init();
}
