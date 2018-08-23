#ifndef adl_texture_h__
#define adl_texture_h__

#include <GL/glew.h>

class adlTexture
{
public:
	adlTexture();
	~adlTexture();

	unsigned int get_id();
	unsigned int get_specular_map_id();

private:

	unsigned int width_;
	unsigned int height_;
	unsigned int texture_id_;
	unsigned int specular_map_id_;
};

#endif // adl_texture_h__