#include "ofApp.h"

void ofApp::initShader()
{
  // ウィンドウサイズを取得
  winW = ofGetWindowWidth();
  winH = ofGetWindowHeight();

  // 結合画像内の画像の行数,列数を計算
  int imgCol = numImg * winW < maxNumSplit ? numImg : floor(maxNumSplit / winW);
  int imgRow = ceil(numImg / float(imgCol));
  int joinedTexW = winW * imgCol;
  int joinedTexH = winH * imgRow;
  // 結合画像サイズが制限を超える場合は画像数を減らす
  if (joinedTexH > maxNumSplit)
  {
    imgRow = floor(maxNumSplit / winH);
    joinedTexH = winH * imgRow;
    numImg = imgCol * imgRow;
    cout << "画像数変更 : " + ofToString(numImg) << endl;
  }

  // 画像を一つの画像に結合
  joinedFbo.allocate(joinedTexW, joinedTexH, GL_RGB);
  joinedFbo.begin();
  for (int y = 0; y < imgRow; y++)
  {
    for (int x = 0; x < imgCol; x++)
    {
      int index = y * imgCol + x;
      if (index < numImg)
        images[index].draw(x * winW, y * winH, winW, winH);
    }
  }
  joinedFbo.end();

  // 空画像のメモリ確保
  emptyImage.allocate(winW, winH, OF_IMAGE_COLOR);

  // 描画シェーダーにデータを送信
  drawShader.load("shader/passthru.vert", "shader/draw.frag");
  drawShader.begin();
  drawShader.setUniform1i("sqrtNumSplit", sqrtNumSplit);
  drawShader.setUniform1i("numSplit", numSplit);
  drawShader.setUniform1i("numImg", numImg);
  drawShader.setUniform1i("imgCol", imgCol);
  drawShader.setUniform2f("winSize", winW, winH);
  drawShader.setUniformTexture("joinedTex", joinedFbo.getTexture(), 1);
  drawShader.end();

  // 分割領域のデータ作成
  vector<float> splitData(numSplit * 3);
  vector<float> dOpacityData(numSplit);
  for (int i = 0; i < numSplit; i++)
  {
    splitData[i * 3 + 0] = ofRandom(1.0);                 // 現在の画像ID
    splitData[i * 3 + 1] = ofRandom(1.0);                 // 次の画像ID
    splitData[i * 3 + 2] = 1.0f;                          // 透明度
    dOpacityData[i] = ofRandom(minDOpacity, maxDOpacity); // 透明度の変化幅
  }
  splitTex.allocate(sqrtNumSplit, sqrtNumSplit, GL_RGB);
  splitTex.src->getTexture().loadData(splitData.data(), sqrtNumSplit, sqrtNumSplit, GL_RGB);
  splitTex.dst->getTexture().loadData(splitData.data(), sqrtNumSplit, sqrtNumSplit, GL_RGB);
  dOpacityTex.loadData(dOpacityData.data(), sqrtNumSplit, sqrtNumSplit, GL_RED);

  // 分割領域のデータ更新シェーダーにデータ送信
  splitShader.load("shader/passthru.vert", "shader/update.frag");
  splitShader.begin();
  splitShader.setUniformTexture("dOpacityTex", dOpacityTex, 4);
  splitShader.end();
}
