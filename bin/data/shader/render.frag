#version 150

uniform int numSplit;
uniform int numImages;
uniform vec2 textureSize;
uniform vec2 windowSize;
uniform sampler2DRect joinedTexture;
uniform sampler2DRect splitAreaData;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / windowSize.xy;
    vec2 coord = vec2(texCoordVarying.x * textureSize.x / windowSize.x, texCoordVarying.y * textureSize.y / windowSize.y);

    // 分割領域毎のデータ取得
    // float splitIndex = uv.x * numSplit; // 縦分割
    // float splitIndex = uv.y * numSplit; //横分割
    // float splitIndex = distance(vec2(0.5, 0.5), uv) * numSplit;  // 楕円分割
    float splitIndex = distance(windowSize/2.0, gl_FragCoord.xy) * 2 / distance(vec2(0), windowSize) * numSplit; // 円分割
    vec4 splitAreaDataTexture = texture(splitAreaData, vec2(splitIndex, 0));
    float currentImageId = splitAreaDataTexture.r;
    float nextImageId = splitAreaDataTexture.g;
    float opatcity = splitAreaDataTexture.b;

    vec4 currentTexture = texture(joinedTexture, vec2(coord.x + int(currentImageId * numImages) * textureSize.x, coord.y));
    vec4 nextTexture = texture(joinedTexture, vec2(coord.x + int(nextImageId * numImages) * textureSize.x, coord.y));
    vec4 color = mix(currentTexture, nextTexture, opatcity);

	outputColor = color;
}
