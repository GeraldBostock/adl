#ifndef adl_memory_h__
#define adl_memory_h__

#define ADL_NEW(Class_name, ...)	new Class_name(__VA_ARGS__);

#define ADL_DELETE(ptr)	\
if(ptr != nullptr)		\
{						\
    delete ptr;			\
    ptr = nullptr;		\
}

#endif // adl_memory_h__
