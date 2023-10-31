#version 150

uniform float elapsedTime;
uniform sampler2DRect dOpacityTex;
uniform sampler2DRect preSplitTex;

in vec2 texCoord;

out vec4 outputColor;

// 分割領域のデータ更新
void main()
{
  // splitData.r : 現在の画像ID
  // splitData.g : 次の画像ID
  // splitData.b : 現在の画像の透明度
  vec4 splitData = texture(preSplitTex, texCoord);
  float dOpacityData = texture(dOpacityTex, texCoord).r; // 透明度の変化幅

  // 透明度(0~1)を0に近づける
  splitData.b -= dOpacityData;

  // 透明度が0.001より大きい時 isSwitch = 0
  // 透明度が0.001より小さい時 isSwitch = 1
  float isSwitch = step(splitData.b, 0.001);
  float isNotSwitch = 1 - isSwitch;

  // isSwitchが1になった時に以下の操作を実行
  // 1. 透明度を1(不透明)に戻す
  // 2. 現在の画像を次の画像と差し替え
  // 3. 次の画像をランダムに変更
  splitData.b += isSwitch;
  splitData.g = splitData.r * isSwitch + splitData.g * isNotSwitch;
  splitData.r = fract(elapsedTime / dOpacityData) * isSwitch + splitData.r * isNotSwitch;

  outputColor = splitData;
}
