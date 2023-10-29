#include "ofApp.h"

void ofApp::initShader()
{
  // ウィンドウサイズを取得
  winW = ofGetWindowWidth();
  winH = ofGetWindowHeight();

  int imgW = winW;
  int imgH = winH;

  // 結合画像内の画像の行数,列数を計算
  int imgCol = numImg * imgW < maxNumSplit ? numImg : floor(maxNumSplit / imgW);
  int imgRow = ceil(numImg / float(imgCol));
  joinedTexW = imgW * imgCol;
  joinedTexH = imgH * imgRow;
  // 結合画像サイズが制限を超える場合は画像数を減らす
  if (maxNumSplit < joinedTexH)
  {
    imgRow = floor(maxNumSplit / imgH);
    joinedTexH = imgH * imgRow;
    numImg = imgCol * imgRow;
  }
  cout << "画像数 : " + ofToString(numImg) << endl;

  // 画像を一つの画像に結合
  joinedFbo.allocate(joinedTexW, joinedTexH, GL_RGB);
  joinedFbo.begin();
  for (int y = 0; y < imgRow; y++)
  {
    for (int x = 0; x < imgCol; x++)
    {
      int index = y * imgCol + x;
      if (index < numImg)
        images[index].draw(x * imgW, y * imgH, imgW, imgH);
    }
  }
  joinedFbo.end();

  // 空画像のメモリ確保
  emptyImage.allocate(winW, winH, OF_IMAGE_COLOR);

  // 描画シェーダーにデータを送信
  renderShader.load("shader/passthru.vert", "shader/render.frag");
  renderShader.begin();
  renderShader.setUniform1i("sqrtNumSplit", sqrtNumSplit);
  renderShader.setUniform1i("numSplit", numSplit);
  renderShader.setUniform1i("numImg", numImg);
  renderShader.setUniform1i("imgCol", imgCol);
  renderShader.setUniform2f("imgSize", imgW, imgH);
  renderShader.setUniform2f("winSize", winW, winH);
  renderShader.setUniformTexture("joinedTex", joinedFbo.getTexture(), 1);
  renderShader.end();

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