#ifndef adlRaycast_callback_h__
#define adlRaycast_callback_h__

#include <iostream>
#include <vector>

#include "reactphysics3d.h"
#include "engine/adl_renderer/adlDebug_renderer.h"

class RaycastCallback : public rp3d::RaycastCallback { 
 
public:

	RaycastCallback() {}
 
   virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) { 
 
      // Display the world hit point coordinates 
      std::cout << "Hit point : " << 
                    info.worldPoint.x << " " <<
                    info.worldPoint.y << " " <<
                    info.worldPoint.z << 
                    std::endl;

	  bodies_.push_back(info.body);
 
      // Return a fraction of 1.0 to gather all hits 
      return rp3d::decimal(1.0); 
    }

   rp3d::CollisionBody* get_body()
   {
	   if (bodies_.size() > 0)
	   {
		   return bodies_.at(bodies_.size() - 1);
	   }
   }

private:
	rp3d::CollisionBody* body_ = nullptr;
	std::vector<rp3d::CollisionBody*> bodies_;
};

#endif //adlRaycast_callback_h__