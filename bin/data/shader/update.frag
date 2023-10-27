#version 150

uniform float elapsedTime;
uniform sampler2DRect opacityDelta;
uniform sampler2DRect backbuffer;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{
  vec4 data = texture(backbuffer, vec2(texCoordVarying));
  float opacityDeltaData = texture(opacityDelta, vec2(texCoordVarying.x, 0)).r;
  data.b = data.b - opacityDeltaData;
  if (data.b < 0.01) {
    data.b = 1.0f;
    data.g = data.r;
    data.r = fract(elapsedTime);
  }

  outputColor = vec4(data.r, data.g, data.b, 1);
}
