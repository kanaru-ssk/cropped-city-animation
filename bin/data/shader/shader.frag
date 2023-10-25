#version 150

uniform int numCrop;
uniform int numImages;
uniform vec2 textureSize;
uniform vec2 windowSize;
uniform sampler2DRect joinedTexture;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / windowSize.xy;
    int imageId = int(gl_FragCoord.x * numCrop / windowSize.x) % numImages;
    vec4 color  = texture(joinedTexture, vec2(texCoordVarying.x + imageId * textureSize.x, texCoordVarying.y));

	outputColor = color;
}
