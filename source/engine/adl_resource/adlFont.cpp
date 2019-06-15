#include "adlFont.h"

#include "engine/adlMemory.h"

adlFont::adlFont()
{
	characters_ = new std::map<char, glyph>();


	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


adlFont::~adlFont()
{
	ADL_DELETE(characters_)
}

std::map<char, glyph>* adlFont::get_character_map()
{
	return characters_;
}

uint32 adlFont::get_vao()
{
	return vao_;
}

uint32 adlFont::get_vbo()
{
	return vbo_;
}