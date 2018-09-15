#include "adlDebug_renderer.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_resource/adlModel.h"
#include "engine/adl_resource/adlStatic_shader.h"

adlDebug_renderer::adlDebug_renderer()
{
}

void adlDebug_renderer::debug_render_sphere(adlVec3 position, adlColor color, float radius)
{
	IDebug_renderable* sphere = ADL_NEW(Sphere_renderable, position, color, radius);
	render_queue_.push_back(sphere);
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

	shader->start();
	
	shader->load_color(color_.to_vec3());
	shader->load_projection_matrix(projection_matrix);
	shader->load_view_matrix(view_matrix);
	shader->load_model_matrix(transform.get_transformation_matrix());

	model->draw(shader);

	shader->stop();
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