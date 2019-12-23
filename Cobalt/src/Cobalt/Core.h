#pragma once

#ifdef  CB_PLATFORM_WINDOWS
	#ifdef CB_BUILD_DLL
		#define COBALT_API __declspec(dllexport)
	#else
		#define COBALT_API __declspec(dllimport)
	#endif // Build DLL
#else
	#error Windows Support Only
#endif //  CB_PLATFORM_WINDOWS


#define BIT(x) (1<<x)