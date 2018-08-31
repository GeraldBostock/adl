#include "adlEntity_factory.h"


adlEntity_factory::adlEntity_factory()
{
}

const std::vector<std::string>& adlEntity_factory::get_all_registered_classes() const
{
	return registered_classes_;
}