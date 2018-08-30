#ifndef common_h__
#define common_h__

#if defined ADL_TARGET_SYSTEM_WINDOWS
#define NOMINMAX
#include <windows.h>
#define SDL_MAIN_HANDLED
#pragma warning( disable : 4201 )
#pragma warning( disable : 4244 )
//Not enough actual parameters for macro 'max'
#pragma warning( disable : 4003 )
//requires a narrowing conversion
#pragma warning( disable : 4838)
static inline void set_error_mode()
{
	_set_error_mode(_OUT_TO_MSGBOX);
}
#endif

#define USE_SDL

#if defined(__GNUC__) || defined(__clang__) || (defined(_MSC_VER) && _MSC_VER >= 1600)
#include <stdint.h>
#elif defined(_MSC_VER)
typedef signed   __int8  int8_t;
typedef unsigned __int8  uint8_t;
typedef signed   __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed   __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed   __int64 int64_t;
typedef unsigned __int64 uint64_t;
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
typedef int16_t wchar_t;
#else
typedef signed   char      int8_t;
typedef unsigned char      uint8_t;
typedef signed   short int int16_t;
typedef unsigned short int uint16_t;
typedef signed   int       int32_t;
typedef unsigned int       uint32_t;
typedef long long          int64_t;
typedef unsigned long long uint64_t;
typedef uint64_t uintptr_t;
typedef int64_t intptr_t;
typedef int16_t wchar_t;
#endif

typedef uint8_t CHART;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef intptr_t intptr;
typedef uintptr_t uintptr;

#endif // common_h__