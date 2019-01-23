#ifndef adl_debug_renderer_h__
#define adl_debug_renderer_h__

#include "engine/adl_math/adlVector.h"
#include "engine/adl_renderer/adlColor.h"

#include <vector>
#include <map>

class IDebug_renderable
{
public:
	IDebug_renderable(adlVec3 position, adlColor color) : position_(position), color_(color) {};
	~IDebug_renderable() {};

	virtual void render() = 0;

protected:
	adlVec3 position_;
	adlColor color_;

private:
};

class Point_renderable : public IDebug_renderable
{
public:
	Point_renderable(adlVec2_i32 position, adlColor color, float size) : IDebug_renderable(adlVec3(0.0f), color), size_(size), screen_pos_(position) {}
	~Point_renderable() {}

	void render() override;

private:
	float size_;
	adlVec2_i32 screen_pos_;
};

class Sphere_renderable : public IDebug_renderable
{
public:
	Sphere_renderable(adlVec3 position, adlColor color, float radius) : IDebug_renderable(position, color), radius_(radius) {}
	~Sphere_renderable() {}

	void render() override;

protected:
private:
	float radius_;
};

class Quad2D_renderable : public IDebug_renderable
{
public:
	Quad2D_renderable(adlVec2_i32 point1, adlVec2_i32 point2, float line_width, adlColor color) : IDebug_renderable(adlVec3(0.0f), color), point1_(point1), point2_(point2), line_width_(line_width) {}
	~Quad2D_renderable() {}

	void render() override;

private:
	adlVec2_i32 point1_;
	adlVec2_i32 point2_;
	float line_width_;
};

class Line2D_renderable : public IDebug_renderable
{
public:
	Line2D_renderable(adlVec2_i32 point1, adlVec2_i32 point2, float line_width, adlColor color) : IDebug_renderable(adlVec3(0.0f), color), point1_(point1), point2_(point2), line_width_(line_width) {}
	~Line2D_renderable() {}

	void render() override;

private:
	adlVec2_i32 point1_;
	adlVec2_i32 point2_;
	float line_width_;
};

class Box_renderable : public IDebug_renderable
{
public:
	Box_renderable(adlVec3 position, float scale, adlColor color) : IDebug_renderable(position, color), scale_(scale) {}
	~Box_renderable() {}

	void render() override;

private:
	float scale_;
};

class Line3D_renderable : public IDebug_renderable
{
public:
	Line3D_renderable(adlVec3 point1, adlVec3 point2, float line_width, adlColor color) : IDebug_renderable(point1, color), point2_(point2), line_width_(line_width) {}
	~Line3D_renderable() {}

	void render() override;

private:
	adlVec3 point2_;
	float line_width_;
};

class adlDebug_renderer
{
public:
	static adlDebug_renderer& get()
	{
		static adlDebug_renderer instance;
		return instance;
	}

	void render_sphere(adlVec3 position, adlColor color, float radius);
	void render_quad_2D(adlVec2_i32 point1, adlVec2_i32 point2, float line_width = 1.0f, adlColor color = adlColor::WHITE);
	void render_line_2D(adlVec2_i32 point1, adlVec2_i32 point2, float line_width = 1.0f, adlColor color = adlColor::WHITE);
	void render_box(adlVec3 position, float scale = 1.0f, adlColor color = adlColor::WHITE);
	void render_line3D(adlVec3 point1, adlVec3 point2, float line_width = 1.0f, adlColor color = adlColor::WHITE);
	void render_point(adlVec2_i32 point, adlColor color = adlColor::WHITE, float size = 1.0f);

private:
	adlDebug_renderer();

	std::vector<IDebug_renderable*> render_queue_;

	friend class adlRoot;

	void render();
	void clear_render_queue();
	void render_bounding_boxes();

	adlColor bounding_box_color_ = adlColor::MAGENTA;
	float bounding_box_line_width_ = 1.0f;

	std::vector<float> line_vertices_;

	std::map<std::pair<adlColor, float>, std::vector<float>> line3Ds_;
	std::vector<std::pair<adlColor, float>> line3D_keys_;
};

#endif // adl_debug_renderer_h__