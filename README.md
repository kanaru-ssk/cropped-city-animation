# Split City

![デモGIF](/demo/split-city.gif)

## 使用方法

1. [openFrameworks](https://openframeworks.cc/)をダウンロード
2. `of_v*_*_release/projectGenerator/projectGenerator`で新しいプロジェクトを作成
3. `of_v*_*_release/apps/myApps/[プロジェクト名]/`配下の`src/`、`bin/data/`の中身をこのリポジトリの内容に置き換え
4. ターミナルを起動し、`[プロジェクト名]/`ディレクトリ内に移動
5. `make Debug`でコンパイル
6. `make RunDebug`で起動

## パラメータ調整

### 分割数変更

`src/ofApp.cpp` line.6 の数値を変更

```c++
sqrtNumSplit = 32;               // 分割数の正の平方根
numSplit = pow(sqrtNumSplit, 2); // 分割数
```

### 画像数変更

`src/ofApp.cpp` line.8 の数値を変更

```c++
numImg = 10; // 画像数
```

### 透明度変化幅変更

`src/ofApp.cpp` line.9-10 の数値を変更

```c++
minDOpacity = 0.01; // 透明度の変化幅の最小値
maxDOpacity = 0.03; // 透明度の変化幅の最大値
```

### 分割方法変更

`bin/data/shader/render.frag` line.20-23 のコメントアウトされたコードに変更

```glsl
// float splitIndex = numSplit * texCoord.x / winSize.x; // 縦分割
// float splitIndex = numSplit * texCoord.y / winSize.y; //横分割
// float splitIndex = numSplit * distance(vec2(0.5), texCoord / winSize);  // 楕円分割
float splitIndex = numSplit * distance(0.5 * winSize, texCoord) * 2 / length(winSize); // 円分割
```
