#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    numSplit = 1024;    // 分割数
    numImages = 11;    // 画像数
    minDOpacity = 0.01; // 透明度の変化幅の最小値
    maxDOpacity = 0.03; // 透明度の変化幅の最大値

    // 画像ロード
    imagesDir.listDir("images"); // bin/data/images/ フォルダ内のjpg画像を取得
    imagesDir.allowExt("jpg");
    if (imagesDir.size() < numImages) {
        numImages = imagesDir.size();

    }
    images.assign(numImages, ofImage());
    for (int i = 0; i < numImages; i++)
    {
        images[i].load(imagesDir.getPath(i)); // imagesに画像をロード
    }

    // テクスチャサイズを設定
    texW = ofGetWindowWidth();
    texH = ofGetWindowHeight();

    // 取得した画像を横に並べた一つの画像に変更
    // [ error ] ofFbo: FRAMEBUFFER_INCOMPLETE_ATTACHMENT
    // テクスチャサイズに制限あり？
    joinedFbo.allocate(texW * numImages, texH);
    joinedFbo.begin();
    for (int i = 0; i < numImages; i++)
    {
        images[i].draw(i * texW, 0, texW, texH);
    }
    joinedFbo.end();

    init();
}

//--------------------------------------------------------------
// renderShaderデータをセット
void ofApp::init()
{
    winW = ofGetWindowWidth();
    winH = ofGetWindowHeight();

    // 空画像のメモリ確保
    emptyImage.allocate(winW, winH, OF_IMAGE_COLOR_ALPHA);

    // 描画シェーダーにデータを送信
    renderShader.load("shader/passthru.vert", "shader/render.frag");
    renderShader.begin();
        renderShader.setUniform1i("numSplit", numSplit);
        renderShader.setUniform1i("numImages", numImages);
        renderShader.setUniform2f("texSize", texW, texH);
        renderShader.setUniform2f("winSize", winW, winH);
        renderShader.setUniformTexture("joinedTex", joinedFbo.getTexture(), 1);
    renderShader.end();

    // 分割領域のデータ作成
    vector<float> splitData(numSplit*3);
    vector<float> dOpacityData(numSplit);
    for (int i = 0; i < numSplit; i++) {
        splitData[i*3 + 0] = ofRandom(1.0); // 現在の画像ID
        splitData[i*3 + 1] = ofRandom(1.0); // 次の画像ID
        splitData[i*3 + 2] = 1.0f; // 透明度
        dOpacityData[i] = ofRandom(minDOpacity, maxDOpacity); // 透明度の変化幅
    }
    splitTex.allocate(numSplit, 1, GL_RGB);
    splitTex.src->getTexture().loadData(splitData.data(), numSplit, 1, GL_RGB);
    splitTex.dst->getTexture().loadData(splitData.data(), numSplit, 1, GL_RGB);
    dOpacityTex.loadData(dOpacityData.data(), numSplit, 1, GL_RED);

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
