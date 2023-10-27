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
    int splitIndex = int(gl_FragCoord.x * numSplit / windowSize.x);
    vec4 imageIds = texture(splitAreaData, vec2(splitIndex, 0));
    vec4 currentTexture = texture(joinedTexture, vec2(coord.x + int(imageIds.r * numImages) * textureSize.x, coord.y));
    vec4 nextTexture = texture(joinedTexture, vec2(coord.x + int(imageIds.g * numImages) * textureSize.x, coord.y));
    vec4 opacites = texture(splitAreaData, vec2(splitIndex, 1));
    vec4 color = mix(nextTexture, currentTexture, opacites.r);

	outputColor = color;
}
