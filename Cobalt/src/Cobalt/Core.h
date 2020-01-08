#pragma once

#ifdef  CB_PLATFORM_WINDOWS
#ifdef COBALT_DYNAMIC
	#ifdef CB_BUILD_DLL
		#define COBALT_API __declspec(dllexport)
	#else
		#define COBALT_API __declspec(dllimport)
	#endif // Build DLL
#else
	#define COBALT_API
#endif
#else
	#error Windows Support Only
#endif //  CB_PLATFORM_WINDOWS


#ifdef CB_ENABLE_ASSERT
	#define COBALT_ASSERT(x, ...) {if(!(x)) {  COBALT_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak();}}
	#define COBALT_CORE_ASSERT(x, ...) {if(!(x)) {  COBALT_CORE_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak();}}

#else
	#define COBALT_ASSERT(x, ...)
	#define COBALT_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define COBALT_BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)