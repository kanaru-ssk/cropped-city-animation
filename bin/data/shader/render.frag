#version 150

uniform int numSplit;
uniform int numImages;
uniform vec2 textureSize;
uniform vec2 windowSize;
uniform sampler2DRect joinedTexture;
uniform sampler2DRect splittedAreaData;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / windowSize.xy;
    vec2 coord = vec2(texCoordVarying.x * textureSize.x / windowSize.x, texCoordVarying.y * textureSize.y / windowSize.y);
    int splitIndex = int(gl_FragCoord.x * numSplit / windowSize.x);
    vec4 splittedAreaDataTexture = texture(splittedAreaData, vec2(splitIndex, 0));
    vec4 currentTexture = texture(joinedTexture, vec2(coord.x + int(splittedAreaDataTexture.r * numImages) * textureSize.x, coord.y));
    vec4 nextTexture = texture(joinedTexture, vec2(coord.x + int(splittedAreaDataTexture.g * numImages) * textureSize.x, coord.y));
    vec4 color = mix(nextTexture, currentTexture, splittedAreaDataTexture.b);

	outputColor = color;

    // vec2 coord = vec2(texCoordVarying.x * textureSize.x / windowSize.x, texCoordVarying.y * textureSize.y / windowSize.y);
    // vec4 currentTexture = texture(joinedTexture, coord);
    // outputColor = vec4(vec3(currentTexture.r), 1);
    

}
