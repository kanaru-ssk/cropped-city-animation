#version 150

uniform float elapsedTime;
uniform sampler2DRect dOpacityTex;
uniform sampler2DRect preTex;

in vec2 texCoord;

out vec4 outputColor;

void main()
{
  vec4 data = texture(preTex, vec2(texCoord));
  float dOpacityData = texture(dOpacityTex, vec2(texCoord.x, 0)).r;

  data.b = data.b - dOpacityData;

  float isSwitch = step(data.b, 0.01);
  float isNotSwitch = 1 - isSwitch;

  data.b = data.b + isSwitch;
  data.g = data.r * isSwitch + data.g * isNotSwitch;
  data.r = fract(elapsedTime / dOpacityData) * isSwitch + data.r * isNotSwitch;

  outputColor = vec4(data.r, data.g, data.b, 1);
}
