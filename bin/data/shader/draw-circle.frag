#version 150

uniform int sqrtNumSplit;        // 分割数の正の平方根
uniform int numSplit;            // 分割数
uniform int numImg;              // 画像数
uniform int imgCol;              // テスクチャの列数
uniform vec2 winSize;            // ウィンドウサイズ
uniform sampler2DRect joinedTex; // 全ての画像を結合したテクスチャ
uniform sampler2DRect splitTex;  // 分割領域のデータテクスチャ R:現在の画像ID G:次の画像ID B:透明度

in vec2 texCoord;

out vec4 outputColor;

// 描画 円分割
void main()
{
	// 分割インデックスを取得
	float splitIndex = numSplit * distance(0.5 * winSize, texCoord) * 2 / length(winSize);

	// 分割領域のデータ取得
	vec4 splitData = texture(splitTex, vec2(int(splitIndex) % sqrtNumSplit, splitIndex / sqrtNumSplit));

	// テクスチャの座標取得
	vec2 coord = texCoord;

	// 現在の画像
	int currentImgId = int(splitData.r * numImg);
	vec4 currentImg = texture(joinedTex, vec2(coord.x + winSize.x * (currentImgId % imgCol), coord.y + winSize.y * (currentImgId / imgCol)));
	
	// 次の画像
	int nextImgId = int(splitData.g * numImg);
	vec4 nextImg = texture(joinedTex, vec2(coord.x + winSize.x * (nextImgId % imgCol), coord.y + winSize.y * (nextImgId / imgCol)));

	outputColor = mix(currentImg, nextImg, splitData.b);
}
