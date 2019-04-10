#ifndef adl_texture_h__
#define adl_texture_h__

#include <GL/glew.h>

#include <vector>

struct Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
};

class adlTexture
{
public:
	adlTexture();
	~adlTexture();

	unsigned int get_id();
	unsigned int get_specular_map_id();

	const std::vector<unsigned char>& get_pixel_array();
	void set_pixel_array(const std::vector<unsigned char>& pixel_array);

	int get_width();
	int get_height();

	void set_width(int width);
	void set_height(int height);

	void set_color_format(float format)
	{
		color_format_ = format;
	}

	void reload_texture();

private:
	std::vector<unsigned char> pixel_array_;

	unsigned int width_;
	unsigned int height_;
	unsigned int texture_id_;
	unsigned int specular_map_id_;
	float color_format_;
};

#endif // adl_texture_h__