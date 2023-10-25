#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    numCrop = 1024;

    dir.listDir("images"); // bin/data/images/ フォルダ内のjpg画像を取得
    dir.allowExt("jpg");
    numImages = dir.size();
    images.assign(numImages, ofImage());
    textureW = ofGetWindowWidth();
    textureH = ofGetWindowHeight();
    cout << "textureW : " + ofToString(textureW) + ",textureH : " + ofToString(textureH) + ",numImages : " + ofToString(numImages) << endl;
    for (int i = 0; i < numImages; i++)
    {
        images[i].load(dir.getPath(i)); // imagesに画像をロード
        images[i].resize(textureW, textureH);
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
        images[i].draw(i * textureW, 0);
    }
    joinedImageFbo.end();

    shader.load("shader/shader");
    shader.begin();
    shader.setUniform1i("numCrop", numCrop);
    shader.setUniform1i("numImages", numImages);
    shader.setUniform2f("textureSize", textureW, textureH);
    shader.setUniform2f("windowSize", windowW, windowH);
    shader.setUniformTexture("joinedTexture", joinedImageFbo.getTexture(), 1);
    shader.end();
}

//--------------------------------------------------------------
void ofApp::update()
{
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
