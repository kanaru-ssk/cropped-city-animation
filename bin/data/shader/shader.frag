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
    int[10] imageIds = int[](0, 2, 1, 0, 1, 0, 2, 1, 0, 1);
    vec2 uv = gl_FragCoord.xy / windowSize.xy;
    vec4 color = vec4(0, 0, 0, 0);
    
    for (int i = 0; i < numCrop; i++) {
        color = mix(color, texture(joinedTexture, vec2(texCoordVarying.x + imageIds[i] * textureSize.x, texCoordVarying.y)), i / float(numCrop) <= uv.x && uv.x < i + 1 / float(numCrop) ? 1 : 0);
    }

	outputColor = color;
}
