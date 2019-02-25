#ifndef adl_physics_subject_h__
#define adl_physics_subject_h__

#include "adlPhysics_observer.h"

#include <vector>

class adlPhysics_subject
{
public:
	void addObserver(adlPhysics_observer* observer)
	{
		bool observer_already_added = std::find(observers_.begin(), observers_.end(), observer) != observers_.end();
		adl_assert(!observer_already_added);

		if (!observer_already_added)
		{
			observers_.push_back(observer);
		}
	}

	void removeObserver(adlPhysics_observer* observer)
	{
		bool observer_in_array = std::find(observers_.begin(), observers_.end(), observer) != observers_.end();
		adl_assert(observer_in_array);

		//if (observer_in_array)
		//{
		//	//remove(vec.begin(), vec.end(), val), vec.end()
		//	observers_.erase(observer);
		//}
	}

public:
	std::vector<adlPhysics_observer*> observers_;
};

#endif //adl_physics_subject_h__