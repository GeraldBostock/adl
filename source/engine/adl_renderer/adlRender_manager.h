#ifndef adl_render_manager_h__
#define adl_render_manager_h__

#include "engine/adlShared_types.h"
#include "engine/adl_math/adlMath.h"
#include "adlCamera.h"
#include "engine/adl_entities/adlActor.h"
#include "engine/adl_entities/adlLight.h"

class adlRender_manager
{
public:
	static adlRender_manager& get()
	{
		static adlRender_manager instance;
		return instance;
	}

	void prepare();
	void render(adlActor_shared_ptr actor);
	void render(adlLight_shared_ptr light);
	void render_text(const std::string& text, adlFont_shared_ptr font, float x, float y, float scale, adlColor color);
	/*void render_mesh(adlModel_shared_ptr model);
	void render_mesh(adlModel model);*/
	void toggle_wire_frame_mode();

	void set_camera(adlCamera* camera);
	void set_light(adlLight_shared_ptr light);

	void set_projection(adlMat4 projection_matrix);

private:
	adlRender_manager();

	bool is_wire_frame_mode_;

	adlMat4 projection_matrix_;

	adlCamera* camera_;
	adlLight_shared_ptr light_;
};

#endif // adl_render_manager_h__