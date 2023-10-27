#version 150

uniform int numSplit;
uniform int numImages;
uniform vec2 texSize;
uniform vec2 winSize;
uniform sampler2DRect joinedTex;
uniform sampler2DRect splitTex;

in vec2 texCoord;

out vec4 outputColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / winSize.xy;
    vec2 coord = vec2(texCoord.x * texSize.x / winSize.x, texCoord.y * texSize.y / winSize.y);

    // 分割領域毎のデータ取得
    // float splitIndex = uv.x * numSplit; // 縦分割
    // float splitIndex = uv.y * numSplit; //横分割
    // float splitIndex = distance(vec2(0.5, 0.5), uv) * numSplit;  // 楕円分割
    float splitIndex = distance(winSize/2.0, gl_FragCoord.xy) * 2 / distance(vec2(0), winSize) * numSplit; // 円分割
    vec4 splitTexTexture = texture(splitTex, vec2(splitIndex, 0));
    float currentImageId = splitTexTexture.r;
    float nextImageId = splitTexTexture.g;
    float opatcity = splitTexTexture.b;

    vec4 currentTexture = texture(joinedTex, vec2(coord.x + int(currentImageId * numImages) * texSize.x, coord.y));
    vec4 nextTexture = texture(joinedTex, vec2(coord.x + int(nextImageId * numImages) * texSize.x, coord.y));
    vec4 color = mix(currentTexture, nextTexture, opatcity);

	outputColor = color;
}
