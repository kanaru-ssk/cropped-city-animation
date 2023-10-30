#include "ofApp.h"

// draw.fragに渡すデータ初期化
void ofApp::initDrawShader()
{
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

  // draw.fragにデータを送信
  drawShader.load("shader/passthru.vert", "shader/draw.frag");
  drawShader.begin();
  drawShader.setUniform1i("sqrtNumSplit", sqrtNumSplit);
  drawShader.setUniform1i("numSplit", numSplit);
  drawShader.setUniform1i("numImg", numImg);
  drawShader.setUniform1i("imgCol", imgCol);
  drawShader.setUniform2f("winSize", winW, winH);
  drawShader.setUniformTexture("joinedTex", joinedFbo.getTexture(), 1);
  drawShader.end();
}
