#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    numCrop = 10;

    dir.listDir("images"); // bin/data/images/ フォルダ内のjpg画像を取得
    dir.allowExt("jpg");
    numImages = dir.size();
    images.assign(numImages, ofImage());
    for (int i = 0; i < numImages; i++)
    {
        images[i].load(dir.getPath(i)); // imagesに画像をロード
        if (textureSize.x < images[i].getWidth())
            textureSize.x = images[i].getWidth();
        if (textureSize.y < images[i].getHeight())
            textureSize.y = images[i].getHeight();
    }
    for (int i = 0; i < numImages; i++)
    {
        images[i].resize(textureSize.x, textureSize.y);
    }
    joinedImageFbo.allocate(textureSize.x * numImages, textureSize.y);

    init();
}

//--------------------------------------------------------------
// shaderデータをセット
void ofApp::init()
{
    windowSize = {ofGetWindowWidth(), ofGetWindowHeight()};

    fbo.allocate(windowSize.x, windowSize.y);
    emptyImage.allocate(windowSize.x, windowSize.y, OF_IMAGE_COLOR_ALPHA);

    joinedImageFbo.begin();
    for (int i = 0; i < numImages; i++)
    {
        images[i].draw(i * textureSize.x, 0);
    }
    joinedImageFbo.end();

    shader.load("shader/shader");
    shader.begin();
    shader.setUniform1i("numCrop", numCrop);
    shader.setUniform1i("numImages", numImages);
    shader.setUniform2f("textureSize", textureSize.x, textureSize.y);
    shader.setUniform2f("windowSize", windowSize.x, windowSize.y);
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
    emptyImage.draw(0, 0, windowSize.x, windowSize.y);
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
