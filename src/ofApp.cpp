#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    cout << "分割数 : " + ofToString(numSplit) << endl;
    if (numSplit < 1 || numSplit > maxNumSplit)
    {
        cout << "分割数は1 ~ " + ofToString(maxNumSplit) + "で設定して下さい。" << endl;
        std::exit(0);
    }

    loadImg();
    cout << "画像数 : " + ofToString(numImg) << endl;

    initShader();
}

//--------------------------------------------------------------
// データ更新処理 シェーダー側のコードは bin/data/shader/update.frag
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
// 描画処理 シェーダー側のコードは bin/data/shader/draw.frag
void ofApp::draw()
{
    // 空画像上に描画シェーダーのテクスチャを描画
    drawShader.begin();
    drawShader.setUniformTexture("splitTex", splitTex.src->getTexture(), 2);
    emptyImage.draw(0, 0, winW, winH);
    drawShader.end();
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
