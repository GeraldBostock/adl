#ifndef adl_render_manager_h__
#define adl_render_manager_h__

#include "engine/adlShared_types.h"

class adlRender_manager
{
public:
	static adlRender_manager& get()
	{
		static adlRender_manager instance;
		return instance;
	}

	void prepare();
	void render_mesh(adlModel_shared_ptr model);

private:
	adlRender_manager();
	~adlRender_manager();
};

#endif // adl_render_manager_h__