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
    vec2 coord = vec2(texCoordVarying.x * textureSize.x / windowSize.x, texCoordVarying.y * textureSize.y / windowSize.y);
    vec2 uv = gl_FragCoord.xy / windowSize.xy;
    int imageId = int(gl_FragCoord.x * numCrop / windowSize.x) % numImages;
    vec4 color  = texture(joinedTexture, vec2(coord.x + imageId * textureSize.x, coord.y));

    // vec4 currentTexture = texture(joinedTexture, vec2(texCoordVarying.x + imageId * textureSize.x, texCoordVarying.y));
    // vec4 nextTexture = texture(joinedTexture, vec2(texCoordVarying.x + nextImageId * textureSize.x, texCoordVarying.y));
    // vec4 color = mix(currentTexture, nextTexture, opacity);

	outputColor = color;
}
