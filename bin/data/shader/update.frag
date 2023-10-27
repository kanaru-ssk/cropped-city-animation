#version 150

uniform float elapsedTime;
uniform sampler2DRect opacityDelta;
uniform sampler2DRect backbuffer;

in vec2 texCoord;

out vec4 outputColor;

void main()
{
  vec4 data = texture(backbuffer, vec2(texCoord));
  float opacityDeltaData = texture(opacityDelta, vec2(texCoord.x, 0)).r;

  data.b = data.b - opacityDeltaData;

  float isSwitch = step(data.b, 0.01);
  float isNotSwitch = 1 - isSwitch;

  data.b = data.b + isSwitch;
  data.g = data.r * isSwitch + data.g * isNotSwitch;
  data.r = fract(elapsedTime / opacityDeltaData) * isSwitch + data.r * isNotSwitch;

  outputColor = vec4(data.r, data.g, data.b, 1);
}
