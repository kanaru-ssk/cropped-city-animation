#version 150

uniform int numImages;
uniform vec2 textureResolution;
uniform vec2 windowResolution;
uniform sampler2DRect joinedTexture;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
    float numCrop = 3.0f;
    vec2 uv = gl_FragCoord.xy / windowResolution.xy;
    vec4 joinedTxt1 = texture(joinedTexture, texCoordVarying.xy);
    vec4 joinedTxt2 = texture(joinedTexture, vec2(texCoordVarying.x + textureResolution.x, texCoordVarying.y));
    vec4 joinedTxt3 = texture(joinedTexture, vec2(texCoordVarying.x + 2 * textureResolution.x, texCoordVarying.y));

    vec4 color = vec4(0, 0, 0, 0);
    color = mix(color, joinedTxt1, uv.x < 1 / numCrop ? 1 : 0);
    color = mix(color, joinedTxt2, 1 / numCrop <= uv.x && uv.x < 2 / numCrop ? 1 : 0);
    color = mix(color, joinedTxt3, 2 / numCrop <= uv.x ? 1 : 0);

	outputColor = color;
}
