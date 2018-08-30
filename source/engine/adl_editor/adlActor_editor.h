#ifndef adl_actor_editor_h__
#define adl_actor_editor_h__

#include "engine/adl_entities/adlActor.h"

class adlActor_editor
{
public:
	adlActor_editor();
	~adlActor_editor();

	void update(std::vector<adlActor_shared_ptr>& actors);
private:
	void actorStats(adlActor_shared_ptr actor, int index);

};

#endif // adl_actor_editor_h__