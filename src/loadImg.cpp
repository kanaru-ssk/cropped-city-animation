#include "ofApp.h"

// bin/data/images/ フォルダ内のjpg画像を取得
void ofApp::loadImg()
{
  ofDirectory imagesDir;
  imagesDir.listDir("images");
  imagesDir.allowExt("jpg");

  numImg = imagesDir.size();

  // 最大画像数より多い場合は取得数を制限する
  if (maxNumImg < numImg)
  {
    numImg = maxNumImg;
  }

  // 画像ロード
  images.assign(numImg, ofImage());
  for (int i = 0; i < numImg; i++)
  {
    images[i].load(imagesDir.getPath(i));
  }
}