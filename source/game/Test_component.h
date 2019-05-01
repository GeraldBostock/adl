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
	}

	virtual void on_mouse_hover_end() override
	{
	}

	virtual void under_mouse() override
	{
	}

private:

};

#endif //test_component_h__