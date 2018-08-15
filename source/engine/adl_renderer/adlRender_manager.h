#ifndef adl_render_manager_h__
#define adl_render_manager_h__

#include "engine/adlShared_types.h"
#include "engine/adl_math/adlMath.h"
#include "adlCamera.h"
#include "engine/adlEntity.h"
#include "engine/adl_renderer/adlLight.h"

class adlRender_manager
{
public:
	static adlRender_manager& get()
	{
		static adlRender_manager instance;
		return instance;
	}

	void prepare();
	void render(adlEntity entity, adlColor color);
	void render(adlLight* light);
	/*void render_mesh(adlModel_shared_ptr model);
	void render_mesh(adlModel model);*/
	void set_wire_frame_mode();

	void set_camera(adlCamera* camera);
	void set_light(adlLight* light);

	void set_projection(adlMat4 projection_matrix);

private:
	adlRender_manager();
	~adlRender_manager();

	bool is_wire_frame_mode_;

	adlMat4 projection_matrix_;

	adlCamera* camera_;
	adlLight* light_;
};

#endif // adl_render_manager_h__