#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Cobalt{

	class COBALT_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core logging macros

#define COBALT_CORE_TRACE(...)     ::Cobalt::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define COBALT_CORE_INFO(...)      ::Cobalt::Log::GetCoreLogger()->info(__VA_ARGS__)
#define COBALT_CORE_WARN(...)      ::Cobalt::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define COBALT_CORE_ERROR(...)     ::Cobalt::Log::GetCoreLogger()->error(__VA_ARGS__)
#define COBALT_CORE_FATAL(...)     ::Cobalt::Log::GetCoreLogger()->critical(__VA_ARGS__)


//Client Log Macros

#define COBALT_TRACE(...)     ::Cobalt::Log::GetClientLogger()->trace(__VA_ARGS__)
#define COBALT_INFO(...)      ::Cobalt::Log::GetClientLogger()->info(__VA_ARGS__)
#define COBALT_WARN(...)      ::Cobalt::Log::GetClientLogger()->warn(__VA_ARGS__)
#define COBALT_ERROR(...)     ::Cobalt::Log::GetClientLogger()->error(__VA_ARGS__)
#define COBALT_FATAL(...)     ::Cobalt::Log::GetClientLogger()->critical(__VA_ARGS__)