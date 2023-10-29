#include "ofApp.h"

void ofApp::exportImg()
{
  string folderName = "outImg";
  string timeStr = ofJoinString(
      {ofToString(ofGetHours()),
       ofToString(ofGetMinutes()),
       ofToString(ofGetSeconds())},
      ":");
  string dateStr = ofJoinString(
      {ofToString(ofGetYear()),
       ofToString(ofGetMonth()),
       ofToString(ofGetDay())},
      "-");

  // split-city_YYYY-MM-DD_HH:MM:SS.jpg
  string fileName = "split-city_" + dateStr + "_" + timeStr + ".jpg";
  ofSaveScreen(folderName + "/" + fileName);

  cout << "スクリーンショット : " + fileName << endl;

  exportImgFlag = false;
}
