#include "adlEntity_factory.h"


adlEntity_factory::adlEntity_factory()
{
}

//std::shared_ptr<void> adlEntity_factory::construct(const std::string& class_name)
//{
//	adlLogger* logger = &adlLogger::get();
//
//	map_type::iterator i = classes_.find(class_name);
//	if (i == classes_.end())
//	{
//		logger->log_error("Class " + class_name + " is not registered");
//		return 0; // or throw or whatever you want
//	}
//	return i->second();
//}
