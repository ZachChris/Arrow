#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Arrow {

		class Log {
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_AppLogger;
		};

}

//---Arrow Logging--------------
#define AR_TRACE(...)    ::Arrow::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AR_INFO(...)     ::Arrow::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AR_WARN(...)     ::Arrow::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AR_ERROR(...)    ::Arrow::Log::GetCoreLogger()->error(__VA_ARGS__)

//---Application----------------
#define APP_TRACE(...)   ::Arrow::Log::GetAppLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)    ::Arrow::Log::GetAppLogger()->info(__VA_ARGS__)
#define APP_WARN(...)    ::Arrow::Log::GetAppLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)   ::Arrow::Log::GetAppLogger()->error(__VA_ARGS__)