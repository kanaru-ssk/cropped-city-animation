#pragma once

#include "ofMain.h"

struct pingPongBuffer
{
public:
  void allocate(int _width, int _height, int _internalFormat = GL_RGBA);
  void swap();
  void clear();

  ofFbo &operator[](int n) { return FBOs[n]; }
  ofFbo *src;
  ofFbo *dst;

private:
  ofFbo FBOs[2];
};
