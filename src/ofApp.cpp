#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    numSplit = 1024;

    imagesDir.listDir("images"); // bin/data/images/ フォルダ内のjpg画像を取得
    imagesDir.allowExt("jpg");
    numImages = imagesDir.size();
    images.assign(numImages, ofImage());
    for (int i = 0; i < numImages; i++)
    {
        images[i].load(imagesDir.getPath(i)); // imagesに画像をロード
    }

    texW = ofGetWindowWidth();
    texH = ofGetWindowHeight();

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

    // 分割領域毎のデータ作成
    vector<float> data(numSplit*3);
    vector<float> dOpacityData(numSplit);
    for (int i = 0; i < numSplit; i++) {
        data[i*3 + 0] = ofRandom(1.0);          // 手前の画像ID
        data[i*3 + 1] = ofRandom(1.0);          // 後ろの画像ID
        data[i*3 + 2] = 0.5f;                   // 透明度
        dOpacityData[i] = ofRandom(0.01, 0.03); // 透明度の変化幅
    }
    splitTex.allocate(numSplit, 1, GL_RGB);
    splitTex.src->getTexture().loadData(data.data(), numSplit, 1, GL_RGB);
    splitTex.dst->getTexture().loadData(data.data(), numSplit, 1, GL_RGB);
    dOpacityTex.loadData(dOpacityData.data(), numSplit, 1, GL_RED);

    // 分割領域シェーダーにデータを送信
    splitShader.load("shader/passthru.vert", "shader/update.frag");
    splitShader.begin();
        splitShader.setUniformTexture("dOpacityTex", dOpacityTex, 4);
    splitShader.end();
}

//--------------------------------------------------------------
void ofApp::update()
{
    //----------------------------------------------------------
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
    renderShader.begin();
        ofClear(0);
        renderShader.setUniformTexture("splitTex", splitTex.src->getTexture(), 2);
    renderShader.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
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
