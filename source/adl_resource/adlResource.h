#ifndef adl_resource_h__
#define adl_resource_h__

#include <string>

#include "adl_debug\adlAssert.h"

class adlResource
{
public:
	adlResource();
	virtual ~adlResource();

	virtual void load() = 0;
	virtual void unload() = 0;

	void set_file_path(std::string file_path)
	{
		file_path_ = file_path;
	}

	std::string get_file_path()
	{
		return file_path_;
	}

	bool is_loaded()
	{
		return is_loaded_;
	}

protected:
	bool is_loaded_ = false;
	std::string file_path_;
};

#endif // adl_resource_h__