#include "adlRender_manager.h"

#include "engine/adl_resource/adlModel.h"

#include <GL/glew.h>

adlRender_manager::adlRender_manager()
{

}

adlRender_manager::~adlRender_manager()
{

}

void adlRender_manager::prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.79f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void adlRender_manager::render_mesh(adlModel_shared_ptr model)
{
	model->draw();
}