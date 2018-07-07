#ifndef adl_resource_manager_h__
#define adl_resource_manager_h__

class adlResource_manager
{
public:
	static adlResource_manager& get()
	{
		static adlResource_manager instance;
		return instance;
	}

private:
	adlResource_manager() {}

	adlResource_manager(adlResource_manager const&) = delete;
	void operator=(adlResource_manager const&)		= delete;
};

#endif // adl_resource_manager_h__

