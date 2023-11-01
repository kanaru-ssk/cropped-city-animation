#include "ofApp.h"

// setup,mousePressed,windowResized で呼び出す
void ofApp::initApp()
{
  // ウィンドウサイズを取得
  winW = ofGetWindowWidth();
  winH = ofGetWindowHeight();

  // guiの値を設定値に反映
  sqrtNumSplit = sqrtNumSplitSlider;
  numImg = numImgSlider;
  minDOpacity = minDOpacitySlider;
  maxDOpacity = maxDOpacitySlider;

  // 空画像のメモリ確保
  emptyImage.allocate(winW, winH, OF_IMAGE_COLOR);

  // シェーダーデータ初期化
  initUpdateShader();
  initDrawShader();
}
