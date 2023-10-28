#version 150

uniform int numSplit;            // 分割数
uniform int numImages;           // 画像数
uniform vec2 texSize;            // 画像サイズ
uniform vec2 winSize;            // ウィンドウサイズ
uniform sampler2DRect joinedTex; // 全ての画像を結合したテクスチャ
uniform sampler2DRect splitTex;  // 分割領域のデータテクスチャ R:現在の画像ID G:次の画像ID B:透明度

in vec2 texCoord;

out vec4 outputColor;

// 描画
void main()
{
    // 分割インデックスを取得
    // float splitIndex = numSplit * texCoord.x / winSize.x; // 縦分割
    // float splitIndex = numSplit * texCoord.y / winSize.y; //横分割
    // float splitIndex = numSplit * distance(vec2(0.5), texCoord / winSize);  // 楕円分割
    float splitIndex = numSplit * distance(0.5 * winSize, texCoord) * 2 / length(winSize); // 円分割

    // 分割領域のデータ取得
    vec4 splitData = texture(splitTex, vec2(splitIndex, 0));

    // テクスチャの座標取得
    vec2 coord = texCoord * texSize / winSize;

    // 現在の画像
    vec4 currentTex = texture(joinedTex, vec2(coord.x + floor(splitData.r * numImages) * texSize.x, coord.y));
    
    // 次の画像
    vec4 nextTex = texture(joinedTex, vec2(coord.x + floor(splitData.g * numImages) * texSize.x, coord.y));

	outputColor = mix(currentTex, nextTex, splitData.b);
}
