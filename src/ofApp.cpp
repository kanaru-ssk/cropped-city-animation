#include "ofApp.h"

// shaderデータをセット
void ofApp::init()
{
    windowWidth = ofGetWindowWidth();
    windowHeight = ofGetWindowHeight();

    fbo.allocate(windowWidth, windowHeight);
    emptyImage.allocate(windowWidth, windowHeight, OF_IMAGE_COLOR_ALPHA);

    joinedImageFbo.begin();
    for (int i = 0; i < dirSize; i++)
    {
        images[i].draw(i * textureWidth, 0);
    }
    joinedImageFbo.end();

    shader.load("shadersGL3/shader");
    shader.begin();
    shader.setUniform1i("numImages", dirSize);
    shader.setUniform2f("textureResolution", textureWidth, textureHeight);
    shader.setUniform2f("windowResolution", windowWidth, windowHeight);
    shader.setUniformTexture("joinedTexture", joinedImageFbo.getTexture(), 1);
    shader.end();
}

//--------------------------------------------------------------
void ofApp::setup()
{
    dir.listDir("images"); // bin/data/images/ フォルダ内のjpg画像を取得
    dir.allowExt("jpg");
    dirSize = dir.size();
    images.assign(dirSize, ofImage());
    for (int i = 0; i < dirSize; i++)
    {
        images[i].load(dir.getPath(i)); // imagesに画像をロード
        if (textureWidth < images[i].getWidth())
            textureWidth = images[i].getWidth();
        if (textureHeight < images[i].getHeight())
            textureHeight = images[i].getHeight();
    }
    for (int i = 0; i < dirSize; i++)
    {
        images[i].resize(textureWidth, textureHeight);
    }
    joinedImageFbo.allocate(textureWidth * dirSize, textureHeight);

    init();
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    shader.begin();
    emptyImage.draw(0, 0, windowWidth, windowHeight);
    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    init();
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
