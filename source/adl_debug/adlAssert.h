#ifndef adl_assert_h__
#define adl_assert_h__

#include <stdio.h>
#include "adl_debug\adlLogger.h"

#ifdef _DEBUG
#define adl_assert(expr) \
		if(!(expr)) \
			failed_assertion(#expr ,__FILE__, __LINE__)
#else
#define adl_assert(expr) ((void)0)
#endif

static inline void failed_assertion(const char* expr, char* file, int line)
{
	std::string expression_string(expr);
	std::string file_string(file);
	std::string line_string = std::to_string(line);

	adlLogger::log_error("Assertion " + expression_string + " failed.\nFile: " + file_string + "\nLine: " + line_string + "\n");
}

#endif // adl_assert_h__