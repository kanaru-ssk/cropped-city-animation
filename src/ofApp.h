#pragma once

#define WEBCAM

#include "ofMain.h"

struct pingPongBuffer {
public:
	void allocate( int _width, int _height, int _internalformat = GL_RGBA){
		// Allocate
		for(int i = 0; i < 2; i++){
			FBOs[i].allocate(_width,_height, _internalformat );
			FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		}

		//Assign
		src = &FBOs[0];
		dst = &FBOs[1];

		// Clean
		clear();
	}

	void swap(){
		std::swap(src,dst);
	}

	void clear(){
		for(int i = 0; i < 2; i++){
			FBOs[i].begin();
			ofClear(0,255);
			FBOs[i].end();
		}
	}

	ofFbo& operator[]( int n ){ return FBOs[n];}
	ofFbo *src;    // Source       ->  Ping
	ofFbo *dst;    // Destination  ->  Pong

private:
	ofFbo FBOs[2]; // Real addresses of ping/pong FBO«s
};

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);

private:
    void init();					   // 初期化関数 setup,mousePressed,windowResized で呼び出す
    int numImages;					 // 画像数
		int numSplit;						 // 分割数
		int winW, winH;					 // ウィンドウサイズ
		int texW, texH;					 // テクスチャサイズ
    ofDirectory imagesDir;	 // imagesディレクトリ
    vector<ofImage> images;  // 画像
    ofFbo joinedFbo;				 // 全ての画像を結合した画像
    ofImage emptyImage;      // 空画像
    ofShader renderShader;   // 描画シェーダー
		ofShader splitShader; 	 // 分割領域のデータ更新シェーダー
    pingPongBuffer splitTex; // 分割領域のデータテクスチャ R:現在の画像ID G:次の画像ID B:透明度
		ofTexture dOpacityTex;   // 透明度の変化幅
};
