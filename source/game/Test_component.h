#ifndef test_component_h__
#define test_component_h__

#include "engine/adl_entities/adlPhysics_component.h"

#include <iostream>

class Test_component : adlPhysics_component
{
public:
	Test_component() 
	{
		REGISTER_COMPONENT(Test_component)
	}
	~Test_component() {}

	virtual void on_mouse_hover_start() override
	{
		std::cout << "Mouse hover start" << std::endl;
	}

	virtual void on_mouse_hover_end() override
	{
		std::cout << "Mouse hover end" << std::endl;
	}

private:

};

#endif //test_component_h__