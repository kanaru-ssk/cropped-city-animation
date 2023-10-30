# Split City

![デモGIF](/bin/data/demo.jpg)

## 使用方法

1. [openFrameworks](https://openframeworks.cc/)をダウンロード
2. `of_v*_*_release/projectGenerator/projectGenerator`で新しいプロジェクトを作成
3. `of_v*_*_release/apps/myApps/[プロジェクト名]/`配下の`src/`、`bin/data/`の中身をこのリポジトリの内容に置き換え
4. ターミナルを起動し、`[プロジェクト名]/`ディレクトリ内に移動
5. `make Debug`でコンパイル
6. `make RunDebug`で起動

## 入力画像の差し替え

`bin/data/images/`配下の画像を入れ替える

## スクリーンショット撮影

起動後、キーボードの`s`キーを押すとスクリーンショットを`bin/data/outImg/`配下にスクリーンショットが保存される

## パラメータ調整

### 分割数変更

`src/ofApp.h` line.27 の数値を変更

```c++
const int sqrtNumSplit = 256; // 分割数の正の平方根
```

分割数はsqrtNumSplitの2乗の値になる

```c++
const int numSplit = sqrtNumSplit * sqrtNumSplit; // 分割数
```

### 画像数変更

`src/ofApp.h` line.28 の数値を変更

```c++
const int maxNumImg = 100; // 最大画像数
```

### 透明度変化幅変更

`src/ofApp.h` line.29-30 の数値を変更

```c++
const float minDOpacity = 0.01; // 透明度の変化幅の最小値
const float maxDOpacity = 0.03; // 透明度の変化幅の最大値
```

### 分割方法変更

`bin/data/shader/draw.frag` line.19-22 のコメントアウトされたコードに変更

```glsl
// float splitIndex = numSplit * texCoord.x / winSize.x; // 縦分割
// float splitIndex = numSplit * texCoord.y / winSize.y; // 横分割
// float splitIndex = numSplit * distance(vec2(0.5), texCoord / winSize);  // 楕円分割
float splitIndex = numSplit * distance(0.5 * winSize, texCoord) * 2 / length(winSize); // 円分割
```
