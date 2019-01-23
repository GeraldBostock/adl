#ifndef adl_terrain_debugger_h__
#define adl_terrain_debugger_h__

class adlTerrain_debugger
{
public:
	adlTerrain_debugger();
	~adlTerrain_debugger();

	void update();
private:
	bool debugger_open_;
	bool draw_normals_;
	bool draw_face_normals_;

	float normal_drawing_radius_;
	float face_normal_radius_;
};

#endif // adl_terrain_debugger_h__