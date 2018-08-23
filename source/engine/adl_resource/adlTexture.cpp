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