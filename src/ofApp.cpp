#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    numSplit = 16;

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
    vector<float> data(numSplit*4);
    for (int i = 0; i < numSplit; i++){
        data[i*2 + 0] = ofRandom(1.0);      // currentImageId;
        data[i*2 + 1] = ofRandom(1.0);      // nextImageId;
        data[numSplit*2 + i*2 + 0] = 0;     // opacity;
        data[numSplit*2 + i*2 + 1] = 0.99f; // switch period;
    }
    splitAreaData.allocate(numSplit, 2, GL_RG);
    splitAreaData.src->getTexture().loadData(data.data(), numSplit, 2, GL_RG);
    splitAreaData.dst->getTexture().loadData(data.data(), numSplit, 2, GL_RG);
    updatesplitAreaShader.load("shader/update");
}

//--------------------------------------------------------------
void ofApp::update()
{
    //----------------------------------------------------------
    splitAreaData.dst->begin();
        ofClear(0);
        updatesplitAreaShader.begin();

            updatesplitAreaShader.setUniform1f("elapsedTime", ofGetElapsedTimef());
            updatesplitAreaShader.setUniformTexture("backbuffer", splitAreaData.src->getTexture(), 3);   // passing the previus velocity information
            splitAreaData.src->draw(0, 0);

        updatesplitAreaShader.end();
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
