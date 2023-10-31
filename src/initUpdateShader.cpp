#include "ofApp.h"

// update.fragに渡すデータ初期化
void ofApp::initUpdateShader()
{
  // 分割領域のデータ作成
  int numSplit = sqrtNumSplit * sqrtNumSplit;
  vector<float> splitData(numSplit * 3);
  vector<float> dOpacityData(numSplit);
  for (int i = 0; i < numSplit; i++)
  {
    splitData[i * 3 + 0] = ofRandom(1.0);                 // 現在の画像ID
    splitData[i * 3 + 1] = ofRandom(1.0);                 // 次の画像ID
    splitData[i * 3 + 2] = 1.0f;                          // 透明度
    dOpacityData[i] = ofRandom(minDOpacity, maxDOpacity); // 透明度の変化幅
  }
  // テクスチャにデータをアタッチ
  splitTex.allocate(sqrtNumSplit, sqrtNumSplit, GL_RGB);
  splitTex.src->getTexture().loadData(splitData.data(), sqrtNumSplit, sqrtNumSplit, GL_RGB);
  splitTex.dst->getTexture().loadData(splitData.data(), sqrtNumSplit, sqrtNumSplit, GL_RGB);
  dOpacityTex.loadData(dOpacityData.data(), sqrtNumSplit, sqrtNumSplit, GL_RED);

  // update.fragにデータ送信
  splitShader.load("shader/passthru.vert", "shader/update.frag");
  splitShader.begin();
  splitShader.setUniformTexture("dOpacityTex", dOpacityTex, 4);
  splitShader.end();
}
