#ifndef adl_font_h__
#define adl_font_h__

#include "engine/common.h"
#include "engine/adl_math/adlVector.h"
#include "GL/glew.h"

#include <map>

struct glyph
{
	uint32 texture_id;
	adlVec2_i32 size;
	adlVec2_i32 bearing;
	uint32 advance;
};

class adlFont
{
public:
	adlFont();
	~adlFont();

	uint32 get_vao();
	uint32 get_vbo();
	std::map<char, glyph>* get_character_map();

private:
	std::map<char, glyph>* characters_;

	uint32 vao_;
	uint32 vbo_;
};

#endif // adl_font_h__