#ifndef adl_entity_h__
#define adl_entity_h__

#include "engine/adlShared_types.h"
#include "engine/adl_resource/adlModel.h"
#include "adlEntity_component.h"

#include <document.h>
#include <map>
#include <vector>

typedef std::map<adlComponent_id, adlEntity_component_shared_ptr> Entity_Components;

class adlEntity
{
public:
	friend class adlEntity_factory;

	explicit adlEntity(adlEntity_id id);
	adlEntity() {};
	~adlEntity();

	virtual void init();
	virtual void update(float dt);
	void destroy();

	unsigned int get_id();
	unsigned int getId();

	const std::string& get_name();
	const std::string& getName();

	void set_name(const std::string& name);
	void setName(const std::string& name);

	const std::string& get_type_name();
	const std::string& getTypeName();

	virtual void deserialize(const rapidjson::Value& json_object);

	bool has_component(const std::string& component_name);

	const std::vector<adlEntity_component_shared_ptr>& get_all_components()
	{
		return components_;
	}

	template <class Component_type> std::weak_ptr<Component_type> get_component(const std::string& component_name)
	{
		for (auto component : components_)
		{
			if (component->get_type_name() == component_name)
			{
				//Found component
				adlEntity_component_shared_ptr entity_component(component);
				std::shared_ptr<Component_type> sub_component(std::static_pointer_cast<Component_type>(entity_component));
				std::weak_ptr<Component_type> weak_sub_component(sub_component);

				return weak_sub_component;
			}
		}

		std::cout << "component not found" << std::endl;
		return std::weak_ptr<Component_type>();
	}

protected:
	std::string type_name;

private:
	void add_component(adlEntity_component_shared_ptr component);
	void remove_component(const std::string& component_name);

	static adlEntity_id current_id;
	adlEntity_id id_;
	std::string name_;
	//Entity_Components components_;
	std::vector<adlEntity_component_shared_ptr> components_;
};

#endif //adl_entity_h__