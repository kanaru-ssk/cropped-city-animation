# Split City

![デモGIF](/bin/data/demo.jpg)

### 使用方法

1. [openFrameworks](https://openframeworks.cc/)をダウンロード
2. `of_v*_*_release/projectGenerator/projectGenerator`で新しいプロジェクトを作成
3. `of_v*_*_release/apps/myApps/[プロジェクト名]/`配下の`src/`、`bin/data/`の中身をこのリポジトリの内容に置き換え
4. ターミナルを起動し、`[プロジェクト名]/`ディレクトリ内に移動
5. `make Debug`でコンパイル
6. `make RunDebug`で起動

### 入力画像の差し替え

`bin/data/loadImg/`配下の画像を入れ替える

### メニュー表示/非表示切り替え

画面をクリックするとパラメータ調整メニューの表示/非表示が切り替わる

### パラメータの反映

パラメータ調整後、ENTERキーを押すと変更が反映される

### スクリーンショット撮影

起動後、キーボードの`s`キーを押すとスクリーンショットを`bin/data/exportImf/`配下にスクリーンショットが保存される