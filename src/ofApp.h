#pragma once

#include "ofMain.h"
#include "pingPongBuffer.h"

#define MAX_TEX_RES 16384 * 16384

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	void init(); // 初期化関数 setup,mousePressed,windowResized で呼び出す

	bool exportImgFlag; // 画像書き出しフラグ
	void exportImg();		// 画像書き出し関数

	int sqrtNumSplit;						// 分割数の正の平方根
	int numSplit;								// 分割数
	int winW, winH;							// ウィンドウサイズ
	vector<ofImage> images;			// bin/data/images内の画像
	int imgW, imgH;							// 画像サイズ
	int numImg;									// 画像数
	ofFbo joinedFbo;						// 結合画像 (全ての画像を結合した画像)
	int joinedTexW, joinedTexH; // 結合画像サイズ
	int imgCol, imgRow;					// テスクチャの列数,行数
	ofImage emptyImage;					// 空画像
	ofShader renderShader;			// 描画シェーダー
	ofShader splitShader;				// 分割領域のデータ更新シェーダー
	pingPongBuffer splitTex;		// 分割領域のデータテクスチャ R:現在の画像ID G:次の画像ID B:透明度
	ofTexture dOpacityTex;			// 透明度の変化幅
	float minDOpacity;					// 透明度の変化幅の最小値
	float maxDOpacity;					// 透明度の変化幅の最大値
};
