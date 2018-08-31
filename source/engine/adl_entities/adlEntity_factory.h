#ifndef adl_entity_factory_h__
#define adl_entity_factory_h__

#include "engine/adl_debug/adlLogger.h"
#include <map>
#include <memory>

template <class T> void* constructor() { return (void*)new T(); }
typedef void*(*constructor_t)();
typedef std::map<std::string, constructor_t> map_type;

#define REGISTER_CLASS(class_name) adlEntity_factory* factory = &adlEntity_factory::get(); \
								   factory->register_class<class_name>(#class_name);

class adlEntity_factory
{
public:
	static adlEntity_factory& get()
	{
		static adlEntity_factory instance;
		return instance;
	}

	template <class T>
	void register_class(const std::string& class_name)
	{
		if (classes_.count(class_name) == 0)
		{
			classes_.insert(std::make_pair(class_name, &constructor<T>));
			registered_classes_.push_back(class_name);
		}
	}

	void* construct(const std::string& class_name)
	{
		adlLogger* logger = &adlLogger::get();

		map_type::iterator i = classes_.find(class_name);
		if (i == classes_.end())
		{
			logger->log_error("Class " + class_name + " is not registered");
			return nullptr;
		}
		return i->second();
	}

	const std::vector<std::string>& get_all_registered_classes() const;


private:
	adlEntity_factory();

	map_type classes_;
	std::vector<std::string> registered_classes_;
};

#endif // adl_entity_factory_h__