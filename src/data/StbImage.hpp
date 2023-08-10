#pragma once
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION


namespace imkanji
{

class StbImage
{
public:
  StbImage(const char * filename);
  StbImage(const StbImage & rhs);
  StbImage & operator=(const StbImage & rhs);
  StbImage(StbImage && rhs);
  StbImage & operator=(StbImage && rhs);
  ~StbImage();

  bool isEmpty() const { return mData == nullptr; }
  void clear();
  GLuint addTexture();
  const unsigned char * data() const { return mData; }
  unsigned char * data() { return mData; }
  unsigned int width() const { return mWidth; }
  unsigned int height() const { return mHeight; }

private:
  unsigned char * mData = nullptr;
  unsigned int mWidth{};
  unsigned int mHeight{};
};

GLuint createTexture(const char * filename);

} // namespace imkanji
