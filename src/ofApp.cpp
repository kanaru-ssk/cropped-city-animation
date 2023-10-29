#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    sqrtNumSplit = 256;                     // 分割数の正の平方根
    numSplit = sqrtNumSplit * sqrtNumSplit; // 分割数
    numImg = 10;                            // 画像数
    minDOpacity = 0.01;                     // 透明度の変化幅の最小値
    maxDOpacity = 0.03;                     // 透明度の変化幅の最大値

    cout << "分割数 : " + ofToString(numSplit) << endl;
    if (numSplit < 1 || MAX_TEX_RES < numSplit)
    {
        cout << "分割数は1 ~ " + ofToString(MAX_TEX_RES) + "で設定して下さい。" << endl;
        std::exit(0);
    }

    // bin/data/images/ フォルダ内のjpg画像を取得
    ofDirectory imagesDir;
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
    init();
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
