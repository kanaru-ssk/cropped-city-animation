#version 150

uniform vec2 textureSize;
uniform vec2 windowSize;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;

void main()
{
    texCoordVarying = vec2(texcoord.x * textureSize.x / windowSize.x, texcoord.y * textureSize.y / windowSize.y);
	gl_Position = modelViewProjectionMatrix * position;
}
