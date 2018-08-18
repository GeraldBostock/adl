#ifndef adl_assert_h__
#define adl_assert_h__

#ifdef ADL_TARGET_SYSTEM_WINDOWS
  #include <crtdbg.h>
  #ifdef _DEBUG
  #define adl_assert(expr) _ASSERTE(expr)
  #else
  #define adl_assert(expr) ((void)0)
  #endif
#elif defined ADL_TARGET_SYSTEM_UNIX
  #include <cassert>
  #ifdef _DEBUG
  #define adl_assert(expr) _ASSERTE(expr)
  #else
  #define adl_assert(expr) ((void)0)
  #endif
#endif

#endif // adl_assert_h__
