#include "adlDebug_renderer.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"
#include "engine/adlWindow.h"
#include "engine/adl_debug/adlLogger.h"
#include "engine/common.h"

adlDebug_renderer::adlDebug_renderer()
{
}

void adlDebug_renderer::render_sphere(adlVec3 position, adlColor color, float radius)
{
	IDebug_renderable* sphere = ADL_NEW(Sphere_renderable, position, color, radius);
	render_queue_.push_back(sphere);
}

void adlDebug_renderer::render_quad_2D(adlVec2_i32 point1, adlVec2_i32 point2, float line_width/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* quad = ADL_NEW(Quad2D_renderable, point1, point2, line_width, color);
	render_queue_.push_back(quad);
}

void adlDebug_renderer::render_line_2D(adlVec2_i32 point1, adlVec2_i32 point2, float line_width/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* line2D = ADL_NEW(Line2D_renderable, point1, point2, line_width, color);
	render_queue_.push_back(line2D);
}

void adlDebug_renderer::render_box(adlVec3 position, float scale/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* box = ADL_NEW(Box_renderable, position, scale, color);
	render_queue_.push_back(box);
}

void adlDebug_renderer::render_line3D(adlVec3 point1, adlVec3 point2, float line_width/* = 1.0f*/, adlColor color/* = adlColor::WHITE*/)
{
	IDebug_renderable* line3D = ADL_NEW(Line3D_renderable, point1, point2, line_width, color);
	render_queue_.push_back(line3D);
}

void Sphere_renderable::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlModel_shared_ptr model = adl_rm->get_model("Sphere");
	adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

	adlTransform transform = adlTransform::identity();

	transform.o = position_;
	transform.scale = adlVec3(radius_);

	const adlMat4& projection_matrix = renderer->get_projection_matrix();
	const adlMat4& view_matrix = scn_manager->get_camera()->get_view_matrix();
	const adlMat4& model_matrix = transform.get_transformation_matrix();

	shader->start();
	
	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_model_matrix(model_matrix);
	shader->load_switch(true);

	model->draw(shader, model_matrix);

	shader->stop();
}

void Quad2D_renderable::render()
{
	adlVec2 ndc1 = adlMath::to_ndc(point1_);
	adlVec2 ndc2 = adlMath::to_ndc(point2_);

	float min_x = adlMath::min2(ndc1.x, ndc2.x);
	float min_y = adlMath::min2(ndc1.y, ndc2.y);

	float max_x = adlMath::max2(ndc1.x, ndc2.x);
	float max_y = adlMath::max2(ndc1.y, ndc2.y);

	glLineWidth(line_width_);
	adlVec3 color_vec = color_.to_vec3();
	glColor3f(color_vec.x, color_vec.y, color_vec.z);
	glBegin(GL_LINES);
	//Left
	glVertex3f(min_x, min_y, 0.0f);
	glVertex3f(min_x, max_y, 0.0f);

	//Bottom
	glVertex3f(min_x, min_y, 0.0f);
	glVertex3f(max_x, min_y, 0.0f);

	//Right
	glVertex3f(max_x, max_y, 0.0f);
	glVertex3f(max_x, min_y, 0.0f);

	//Top
	glVertex3f(max_x, max_y, 0.0f);
	glVertex3f(min_x, max_y, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void Line2D_renderable::render()
{
	adlVec2 ndc1 = adlMath::to_ndc(point1_);
	adlVec2 ndc2 = adlMath::to_ndc(point2_);

	glLineWidth(line_width_);
	adlVec3 color_vec = color_.to_vec3();
	glColor3f(color_vec.x, color_vec.y, color_vec.z);
	glBegin(GL_LINES);
	glVertex3f(ndc1.x, ndc1.y, 0.0f);
	glVertex3f(ndc2.x, ndc2.y, 0.0f);
	glEnd();
	glLineWidth(1.0f);
}

void Box_renderable::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlModel_shared_ptr model = adl_rm->get_model("Cube");
	adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

	adlTransform transform = adlTransform::identity();

	transform.o = position_;
	transform.scale = adlVec3(scale_);

	const adlMat4& projection_matrix = renderer->get_projection_matrix();
	const adlMat4& view_matrix = scn_manager->get_camera()->get_view_matrix();
	const adlMat4& model_matrix = transform.get_transformation_matrix();

	shader->start();

	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_model_matrix(model_matrix);
	shader->load_switch(true);

	model->draw(shader, model_matrix);

	shader->stop();
}

void Line3D_renderable::render()
{
	adlRender_manager* renderer = &adlRender_manager::get();
	adlScene_manager* scn_manager = &adlScene_manager::get();

	adlMat4 projection_matrix = renderer->get_projection_matrix();
	adlMat4 view_matrix = scn_manager->get_camera()->get_view_matrix();

	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlShader_shared_ptr shader = adl_rm->get_shader("debug_render");

	adlVec3 p1 = adlVec4(position_.x, position_.y, position_.z, 1.0f);
	adlVec3 p2 = adlVec4(point2_.x, point2_.y, point2_.z, 1.0f);

	float points[] = { p1.x, p1.y, p1.z, p2.x, p2.y, p2.z };
	uint32 vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uint32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &points[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glLineWidth(line_width_);
	shader->start();

	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_switch(false);

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);

	glBindVertexArray(0);

	shader->stop();
	glLineWidth(1.0f);
}

void adlDebug_renderer::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_DEPTH_TEST);

	for (auto renderable : render_queue_)
	{
		renderable->render();
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void adlDebug_renderer::clear_render_queue()
{
	for (auto renderable : render_queue_)
	{
		ADL_DELETE(renderable);
	}

	render_queue_.clear();
}