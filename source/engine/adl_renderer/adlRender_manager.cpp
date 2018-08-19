#include "adlRender_manager.h"

#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlFont.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adlWindow.h"

#include <iostream>
#include <GL/glew.h>

adlRender_manager::adlRender_manager()
{
	is_wire_frame_mode_ = false;
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

adlRender_manager::~adlRender_manager()
{

}

void adlRender_manager::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void adlRender_manager::render(adlEntity entity, adlColor color)
{
	adlModel_shared_ptr model = entity.get_model();
	adlMat4 view_matrix = camera_->get_view_matrix();
	adlShader_shared_ptr shader = model->get_shader();
	shader->start();
	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * entity.get_frame().get_transformation_matrix();
	shader->load_mvp(mvp_matrix);
	shader->load_object_color(color.to_vec3());
	shader->load_light_color(light_->get_color().to_vec3());
	shader->load_light_position(light_->get_frame().o);
	shader->load_model_matrix(entity.get_frame().get_transformation_matrix());
	shader->load_camera_position(camera_->get_position());

	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	model->draw();
	shader->stop();
}

void adlRender_manager::render(adlLight* light)
{
	adlModel_shared_ptr model = light->get_model();
	adlMat4 view_matrix = camera_->get_view_matrix();
	adlShader_shared_ptr shader = light->get_shader();
	shader->start();
	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * light->get_frame().get_transformation_matrix();
	shader->load_mvp(mvp_matrix);
	shader->load_light_color(light_->get_color().to_vec3());

	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	model->draw();
	shader->stop();
}

void adlRender_manager::render_text(const std::string& text, adlFont_shared_ptr font, float x, float y, float scale, adlColor color)
{
	adlResource_manager* rm = &adlResource_manager::get();
	adlShader_shared_ptr font_shader = rm->get_shader("font_shader");

	adlWindow* window = adlWindow::get();

	adlMat4 proj = adlMath::create_ortho_projection_matrix(0, window->get_width(), 0, window->get_height());

	font_shader->start();

	font_shader->load_projection_matrix(proj);
	font_shader->load_text_color(color.to_vec3());

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(font->get_vao());

	std::map<char, glyph>* characters = font->get_character_map();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		glyph ch = characters->at(*c);

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.texture_id);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, font->get_vbo());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	font_shader->stop();
}

void adlRender_manager::set_wire_frame_mode()
{
	is_wire_frame_mode_ = !is_wire_frame_mode_;
}

void adlRender_manager::set_projection(adlMat4 projection_matrix)
{
	projection_matrix_ = projection_matrix;
}

void adlRender_manager::set_camera(adlCamera* camera)
{
	camera_ = camera;
}

void adlRender_manager::set_light(adlLight* light)
{
	light_ = light;
}
