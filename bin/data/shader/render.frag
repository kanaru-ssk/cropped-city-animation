#version 150

uniform int numSplit;            // 分割数
uniform int numImages;           // 画像数
uniform vec2 texSize;            // 画像サイズ
uniform vec2 winSize;            // ウィンドウサイズ
uniform sampler2DRect joinedTex; // 全ての画像を結合したテクスチャ
uniform sampler2DRect splitTex;  // 分割領域毎のデータテクスチャ

in vec2 texCoord;

out vec4 outputColor;

// 描画処理
void main()
{
    // ピクセルの分割インデックスを取得
    // float splitIndex = gl_FragCoord.xy / winSize.xy * numSplit; // 縦分割
    // float splitIndex = gl_FragCoord.xy / winSize.xy * numSplit; //横分割
    // float splitIndex = distance(vec2(0.5), gl_FragCoord.xy / winSize.xy) * numSplit;  // 楕円分割
    float splitIndex = distance(winSize / 2, gl_FragCoord.xy) * 2 / length(winSize) * numSplit; // 円分割

    // 分割領域毎のデータを取得
    vec4 splitData = texture(splitTex, vec2(splitIndex, 0));

    // テクスチャの座標を取得
    vec2 coord = texCoord * texSize / winSize;

    // 手前の画像
    vec4 currentTex = texture(joinedTex, vec2(coord.x + int(splitData.r * numImages) * texSize.x, coord.y));
    
    // 後ろの画像
    vec4 nextTex = texture(joinedTex, vec2(coord.x + int(splitData.g * numImages) * texSize.x, coord.y));

	outputColor = mix(currentTex, nextTex, splitData.b);
}
