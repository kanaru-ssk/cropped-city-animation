#include "ofApp.h"

// 一桁の数字に0を追加 1 -> 01
string toPaddingString(int num)
{
  string str = ofToString(num);
  return num < 10 ? "0" + str : str;
}

void ofApp::exportImg()
{
  string timeStr =
      toPaddingString(ofGetHours()) +
      toPaddingString(ofGetMinutes()) +
      toPaddingString(ofGetSeconds());
  string dateStr =
      ofToString(ofGetYear()) +
      toPaddingString(ofGetMonth()) +
      toPaddingString(ofGetDay());

  // split-city_YYYYMMDD_HHMMSS.jpg
  string fileName = "split-city_" + dateStr + "_" + timeStr + ".jpg";
  ofSaveScreen("outImg/" + fileName);

  cout << "スクリーンショット : " + fileName << endl;
}
