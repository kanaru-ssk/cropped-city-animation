#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    numSplit = 1024;

    dir.listDir("images"); // bin/data/images/ フォルダ内のjpg画像を取得
    dir.allowExt("jpg");
    numImages = dir.size();
    images.assign(numImages, ofImage());
    textureW = ofGetWindowWidth();
    textureH = ofGetWindowHeight();
    for (int i = 0; i < numImages; i++)
    {
        images[i].load(dir.getPath(i)); // imagesに画像をロード
    }

    // [ error ] ofFbo: FRAMEBUFFER_INCOMPLETE_ATTACHMENT
    // テクスチャサイズに制限あり？
    joinedImageFbo.allocate(textureW * numImages, textureH);

    init();
}

//--------------------------------------------------------------
// shaderデータをセット
void ofApp::init()
{
    windowW = ofGetWindowWidth();
    windowH = ofGetWindowHeight();

    fbo.allocate(windowW, windowH);
    emptyImage.allocate(windowW, windowH, OF_IMAGE_COLOR_ALPHA);

    joinedImageFbo.begin();
    for (int i = 0; i < numImages; i++)
    {
        images[i].draw(i * textureW, 0, textureW, textureH);
    }
    joinedImageFbo.end();

    shader.load("shader/render");
    shader.begin();
        shader.setUniform1i("numSplit", numSplit);
        shader.setUniform1i("numImages", numImages);
        shader.setUniform2f("textureSize", textureW, textureH);
        shader.setUniform2f("windowSize", windowW, windowH);
        shader.setUniformTexture("joinedTexture", joinedImageFbo.getTexture(), 1);
    shader.end();

    // 分割領域毎のデータ作成
    vector<float> data(numSplit*3);
    vector<float> opacityDeltaData(numSplit);
    for (int i = 0; i < numSplit; i++){
        data[i*3 + 0] = ofRandom(1.0);         // currentImageId
        data[i*3 + 1] = ofRandom(1.0);         // nextImageId
        data[i*3 + 2] = 0.5f;                  // opacity
        opacityDeltaData[i] = ofRandom(0.001, 0.020); // opacityDelta
    }
    splitAreaData.allocate(numSplit, 1, GL_RGB);
    splitAreaData.src->getTexture().loadData(data.data(), numSplit, 1, GL_RGB);
    splitAreaData.dst->getTexture().loadData(data.data(), numSplit, 1, GL_RGB);
    opacityDelta.loadData(opacityDeltaData.data(), numSplit, 1, GL_RED);
    updateSplitAreaShader.load("shader/update");
    updateSplitAreaShader.begin();
        updateSplitAreaShader.setUniformTexture("opacityDelta", opacityDelta, 4);
    updateSplitAreaShader.end();

}

//--------------------------------------------------------------
void ofApp::update()
{
    //----------------------------------------------------------
    splitAreaData.dst->begin();
        ofClear(0);
        updateSplitAreaShader.begin();

            updateSplitAreaShader.setUniform1f("elapsedTime", ofGetElapsedTimef());
            updateSplitAreaShader.setUniformTexture("backbuffer", splitAreaData.src->getTexture(), 3);
            splitAreaData.src->draw(0, 0);

        updateSplitAreaShader.end();
    splitAreaData.dst->end();
    
    splitAreaData.swap();

    //----------------------------------------------------------
    shader.begin();
        ofClear(0);
        shader.setUniformTexture("splitAreaData", splitAreaData.src->getTexture(), 2);
    shader.end();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    shader.begin();
        emptyImage.draw(0, 0, windowW, windowH);
    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    init();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    init();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
