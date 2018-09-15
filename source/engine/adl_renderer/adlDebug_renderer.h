#ifndef adl_debug_renderer_h__
#define adl_debug_renderer_h__

#include "engine/adl_math/adlVector.h"
#include "engine/adl_renderer/adlColor.h"

#include <vector>

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

class Sphere_renderable : public IDebug_renderable
{
public:
	Sphere_renderable(adlVec3 position, adlColor color, float radius) : IDebug_renderable(position, color), radius_(radius){};
	~Sphere_renderable() {};

	void render() override;

protected:
private:
	float radius_;
};

class adlDebug_renderer
{
public:
	static adlDebug_renderer& get()
	{
		static adlDebug_renderer instance;
		return instance;
	}

	void render();

	void debug_render_sphere(adlVec3 position, adlColor color, float radius);

	void clear_render_queue();

private:
	adlDebug_renderer();

	std::vector<IDebug_renderable*> render_queue_;
};

#endif // adl_debug_renderer_h__