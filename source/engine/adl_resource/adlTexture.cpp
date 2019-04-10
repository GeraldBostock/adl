#include "adlTexture.h"


adlTexture::adlTexture()
{
	glGenTextures(1, &texture_id_);
	glGenTextures(1, &specular_map_id_);
}


adlTexture::~adlTexture()
{
}

unsigned int adlTexture::get_id()
{
	return texture_id_;
}

unsigned int adlTexture::get_specular_map_id()
{
	return specular_map_id_;
}

void adlTexture::reload_texture()
{
	glBindTexture(GL_TEXTURE_2D, texture_id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, color_format_, GL_UNSIGNED_BYTE, &pixel_array_[0]);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void adlTexture::set_pixel_array(const std::vector<unsigned char>& pixel_array)
{
	pixel_array_ = pixel_array;
}

const std::vector<unsigned char>& adlTexture::get_pixel_array()
{
	return pixel_array_;
}

int adlTexture::get_width()
{
	return width_;
}

int adlTexture::get_height()
{
	return height_;
}

void adlTexture::set_width(int width)
{
	width_ = width;
}

void adlTexture::set_height(int height)
{
	height_ = height;
}