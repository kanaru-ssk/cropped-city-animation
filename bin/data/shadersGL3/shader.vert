#version 150

uniform int numImages;
uniform vec2 textureResolution;
uniform vec2 windowResolution;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;

void main()
{
    float numCrop = 3.0f;
    texCoordVarying = vec2(texcoord.x * textureResolution.x / windowResolution.x, texcoord.y * textureResolution.y / windowResolution.y);
	gl_Position = modelViewProjectionMatrix * position;
}
