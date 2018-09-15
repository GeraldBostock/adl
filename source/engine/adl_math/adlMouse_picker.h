#ifndef adl_mouse_picker_h__
#define adl_mouse_picker_h__

#include "adlRay.h"
#include "adlMatrix.h"

class adlMouse_picker
{
public:
	static adlMouse_picker& get()
	{
		static adlMouse_picker instance;
		return instance;
	}

	adlRay get_mouse_ray();

	void update(adlMat4 projection_matrix, adlMat4 view_matrix);

private:
	adlRay mouse_ray_;

	adlRay calculate_mouse_ray();
	adlVec2 calculate_normalized_device_coords(float mouse_x, float mouse_y);
	adlVec4 to_eye_coordinates(adlVec4 clip_coordinates);

	adlMat4 projection_matrix_;
	adlMat4 view_matrix_;

	adlMouse_picker();
};

#endif // adl_mouse_picker_h__