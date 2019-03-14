#include "adlBullet_debug_drawer.h"

#include "../../adl_renderer/adlDebug_renderer.h"
#include "../../adl_debug/adlLogger.h"

#include <string>

void adlBullet_debug_drawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	adlDebug_renderer* db_renderer = &adlDebug_renderer::get();

	db_renderer->render_line3D(adlVec3(from.x(), from.y(), from.z()), adlVec3(to.x(), to.y(), to.z()), 1.0f, adlColor(color.x(), color.y(), color.z()));
}

void adlBullet_debug_drawer::reportErrorWarning(const char* warningString)
{
	adlLogger* logger = &adlLogger::get();

	logger->log_error("Bullet Physics Error: " + std::string(warningString));
}

void adlBullet_debug_drawer::setDebugMode(int debugMode)
{
	debug_modes_ = (DebugDrawModes)debugMode;
}

int adlBullet_debug_drawer::getDebugMode() const
{
	return debug_modes_;
}

void adlBullet_debug_drawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
}

void adlBullet_debug_drawer::draw3dText(const btVector3& location, const char* textString)
{

}