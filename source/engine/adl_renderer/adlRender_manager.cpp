#include "adlRender_manager.h"

#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlFont.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlMaterial.h"
#include "engine/adl_resource/adlTexture.h"
#include "engine/adlWindow.h"
#include "engine/adl_renderer/adlDebug_renderer.h"

#include <iostream>
#include <GL/glew.h>

adlRender_manager::adlRender_manager()
{
	init();
}

void adlRender_manager::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void adlRender_manager::init()
{
	is_wire_frame_mode_ = false;
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void adlRender_manager::render(adlActor_shared_ptr actor)
{
	adl_assert(sun_);
	adlColor color = actor->get_color();
	if (is_wire_frame_mode_)
	{
		color = adlColor::WHITE;
	}
	adlModel_shared_ptr model = actor->get_model();
	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlMaterial_shared_ptr material = actor->get_material();
	if (model == nullptr)
	{
		material = adl_rm->get_material("blank_material");
		model = adl_rm->get_model("Cube");
	}
	adl_assert(model);

	adlMat4 view_matrix = camera_->get_view_matrix();

	adlShader_shared_ptr shader;
	if (material != nullptr)
	{
		if (material->get_texture() != nullptr)
		{
			shader = adl_rm->get_shader("textured");
		}
		else
		{
			shader = adl_rm->get_shader("no_texture");
		}
	}
	else
	{
		shader = adl_rm->get_shader("no_texture");
	}
	adl_assert(shader);

	shader->start();

	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * actor->get_transform().get_transformation_matrix();
	adlMat4 model_matrix = actor->get_transform().get_transformation_matrix();
	shader->load_mvp(mvp_matrix);
	shader->load_light(sun_);
	shader->load_model_matrix(model_matrix);
	shader->load_camera_position(camera_->get_position());
	shader->load_point_lights(lights_);


	if (material != nullptr)
	{
		shader->load_material(material);
		if (material->get_texture() != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material->get_texture()->get_id());
			shader->load_texture();

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, material->get_texture()->get_specular_map_id());
		}
	}
	model->draw(shader, model_matrix);
	shader->stop();
}

void adlRender_manager::render(adlSun_shared_ptr light)
{
	adl_assert(light);
	adlModel_shared_ptr model = light->get_model();
	adl_assert(model);
	adlMat4 view_matrix = camera_->get_view_matrix();
	adlShader_shared_ptr shader = light->get_shader();
	adl_assert(shader);

	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * light->get_transform().get_transformation_matrix();

	shader->start();
	shader->load_mvp(mvp_matrix);
	shader->load_light_color(light->get_color().to_vec3());
	//shader->load_light_color(light_->get_color().to_vec3());

	model->draw(shader, light->get_transform().get_transformation_matrix());
	shader->stop();
}

void adlRender_manager::render(adlPoint_light_shared_ptr point_light)
{
	adl_assert(point_light);
	adlModel_shared_ptr model = point_light->get_model();
	adl_assert(model);
	adlMat4 view_matrix = camera_->get_view_matrix();
	adlShader_shared_ptr shader = point_light->get_shader();
	adl_assert(shader);

	adlMat4 mvp_matrix = projection_matrix_ * view_matrix * point_light->get_transform().get_transformation_matrix();

	shader->start();
	shader->load_mvp(mvp_matrix);
	shader->load_light_color(point_light->get_diffuse().normalize());

	model->draw(shader, point_light->get_transform().get_transformation_matrix());
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

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void adlRender_manager::toggle_wire_frame_mode()
{
	is_wire_frame_mode_ = !is_wire_frame_mode_;

	if (is_wire_frame_mode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void adlRender_manager::set_projection(adlMat4 projection_matrix)
{
	projection_matrix_ = projection_matrix;
}

void adlRender_manager::set_camera(adlCamera* camera)
{
	camera_ = camera;
}

void adlRender_manager::set_sun(adlSun_shared_ptr light)
{
	sun_ = light;
}

void adlRender_manager::set_lights(const std::vector<adlPoint_light_shared_ptr>& lights)
{
	lights_ = lights;
}

adlMat4 adlRender_manager::get_projection_matrix()
{
	return projection_matrix_;
}