#ifndef adl_assert_h__
#define adl_assert_h__

#include <cassert>
#include <crtdbg.h>

#include <stdio.h>
#include "engine/adl_debug/adlLogger.h"

#ifdef _DEBUG
#define adl_assert(expr) _ASSERTE(expr)
#else
#define adl_assert(expr) ((void)0)
#endif

#endif // adl_assert_h__