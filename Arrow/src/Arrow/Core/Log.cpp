#include "arpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Arrow {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("ARROW ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_AppLogger = spdlog::stdout_color_mt("SANDBOX");
		s_AppLogger->set_level(spdlog::level::trace);
	}
}