#include "pingPongBuffer.h"

void pingPongBuffer::allocate(int _width, int _height, int _internalFormat)
{
  for (int i = 0; i < 2; i++)
  {
    FBOs[i].allocate(_width, _height, _internalFormat);
    FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  }

  src = &FBOs[0];
  dst = &FBOs[1];

  clear();
}

void pingPongBuffer::swap()
{
  std::swap(src, dst);
}

void pingPongBuffer::clear()
{
  for (int i = 0; i < 2; i++)
  {
    FBOs[i].begin();
    ofClear(0, 255);
    FBOs[i].end();
  }
}
