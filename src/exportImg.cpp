#include "ofApp.h"

string toPaddingString(int num)
{
  string str = ofToString(num);
  return num < 10 ? "0" + str : str;
}

void ofApp::exportImg()
{
  string folderName = "outImg";
  string timeStr = ofJoinString(
      {toPaddingString(ofGetHours()),
       toPaddingString(ofGetMinutes()),
       toPaddingString(ofGetSeconds())},
      "");
  string dateStr = ofJoinString(
      {ofToString(ofGetYear()),
       toPaddingString(ofGetMonth()),
       toPaddingString(ofGetDay())},
      "");

  // split-city_YYYYMMDD_HHMMSS.jpg
  string fileName = "split-city_" + dateStr + "_" + timeStr + ".jpg";
  ofSaveScreen(folderName + "/" + fileName);

  cout << "スクリーンショット : " + fileName << endl;
}
