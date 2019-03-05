#ifndef adl_entity_h__
#define adl_entity_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlModel.h"
#include "adlEntity_component.h"

#include <document.h>
#include <map>

typedef std::map<adlComponent_id, adlEntity_component_shared_ptr> Entity_Components;

class adlEntity
{
public:
	explicit adlEntity(adlEntity_id id);
	adlEntity() {};
	~adlEntity();

	virtual void init();
	virtual void update(float dt);

	unsigned int get_id();
	unsigned int getId();

	const std::string& get_name();
	const std::string& getName();

	void set_name(const std::string& name);
	void setName(const std::string& name);

	const std::string& get_type_name();
	const std::string& getTypeName();

	virtual void deserialize(const rapidjson::Value& json_object);

	void add_component(adlEntity_component_shared_ptr);

	template <class Component_type> std::weak_ptr<Component_type> get_component(adlComponent_id id)
	{
		Entity_Components::iterator it = components_.find(id);

		//Found component
		if (it != components_.end())
		{
			adlEntity_component_shared_ptr component(it->second);
			std::shared_ptr<Component_type> sub_component(std::static_pointer_cast<Component_type>(component));
			std::weak_ptr<Component_type> weak_sub_component(sub_component);

			return weak_sub_component;
		}
		else
		{
			return std::weak_ptr<Component_type>();
		}
	}

	template <class Component_type> std::weak_ptr<Component_type> get_component(const std::string& component_name)
	{
		for (Entity_Components::iterator it = components_.begin(); it != components_.end(); ++it)
		{
			if (it->second->get_type_name() == component_name)
			{
				//Found component
				adlEntity_component_shared_ptr component(it->second);
				std::shared_ptr<Component_type> sub_component(std::static_pointer_cast<Component_type>(component));
				std::weak_ptr<Component_type> weak_sub_component(sub_component);

				return weak_sub_component;
			}
			else
			{
				return std::weak_ptr<Component_type>();
			}
		}
	}

protected:
	std::string type_name;

private:
	static adlEntity_id current_id;
	adlEntity_id id_;
	std::string name_;
	Entity_Components components_;
};

#endif //adl_entity_h__