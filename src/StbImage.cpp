#include "StbImage.hpp"

#include <stb/stb_image.h>


imkanji::StbImage::StbImage(const char * filename)
{
  int image_width = 0;
  int image_height = 0;
  mData = stbi_load(filename, &image_width, &image_height, nullptr, 4);
  if (mData == nullptr)
    return;

  mWidth = image_width;
  mHeight = image_height;
}

imkanji::StbImage::StbImage(const StbImage & rhs)
{
  if (this == &rhs)
    return;
  this->clear();
  this->mData = reinterpret_cast<unsigned char *>(strdup(reinterpret_cast<char *>(rhs.mData)));
  this->mHeight = rhs.mHeight;
  this->mWidth = rhs.mWidth;
}

imkanji::StbImage & imkanji::StbImage::operator=(const StbImage & rhs)
{
  if (this == &rhs)
    return *this;
  this->clear();
  this->mData = reinterpret_cast<unsigned char *>(strdup(reinterpret_cast<char *>(rhs.mData)));
  this->mHeight = rhs.mHeight;
  this->mWidth = rhs.mWidth;
  return *this;
}

imkanji::StbImage::StbImage(StbImage && rhs)
{
  if (this == &rhs)
    return;
  this->clear();
  this->mData = rhs.mData;
  this->mHeight = rhs.mHeight;
  this->mWidth = rhs.mWidth;
  rhs.mData = nullptr;
  rhs.mHeight = 0;
  rhs.mWidth = 0;
}

imkanji::StbImage & imkanji::StbImage::operator=(StbImage && rhs)
{
  if (this == &rhs)
    return *this;
  this->clear();
  this->mData = rhs.mData;
  this->mHeight = rhs.mHeight;
  this->mWidth = rhs.mWidth;
  rhs.mData = nullptr;
  rhs.mHeight = 0;
  rhs.mWidth = 0;
  return *this;
}

imkanji::StbImage::~StbImage()
{
  if (mData != nullptr)
    stbi_image_free(mData);
}

void imkanji::StbImage::clear()
{
  if (mData != nullptr)
    stbi_image_free(mData);
  mData = nullptr;
}

GLuint imkanji::StbImage::addTexture()
{
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mData);
  return texture;
}

GLuint imkanji::createTexture(const char * filename)
{
  return StbImage{filename}.addTexture();
}
