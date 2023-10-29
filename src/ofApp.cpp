#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    cout << "分割数 : " + ofToString(numSplit) << endl;
    if (numSplit < 1 || maxNumSplit < numSplit)
    {
        cout << "分割数は1 ~ " + ofToString(maxNumSplit) + "で設定して下さい。" << endl;
        std::exit(0);
    }

    loadImg();
    initShader();
}

//--------------------------------------------------------------
void ofApp::update()
{
    splitTex.dst->begin();
    splitShader.begin();

    splitShader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    splitShader.setUniformTexture("preSplitTex", splitTex.src->getTexture(), 3);
    splitTex.src->draw(0, 0);

    splitShader.end();
    splitTex.dst->end();

    splitTex.swap();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // 空画像上に描画シェーダーのテクスチャを描画
    renderShader.begin();
    renderShader.setUniformTexture("splitTex", splitTex.src->getTexture(), 2);
    emptyImage.draw(0, 0, winW, winH);
    renderShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 's')
        exportImg();
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
    initShader();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    initShader();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
