#version 150

uniform float elapsedTime;
uniform sampler2DRect backbuffer;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
  vec4 color = texture(backbuffer, texCoordVarying);

  outputColor = color;
}
