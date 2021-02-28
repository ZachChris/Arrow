#pragma once

#include <memory>
#include "Log.h"

#ifdef PLATFORM_WINDOWS

#else
	#error Arrow Engine supports only windows x64
#endif

#define ASSERT(x, ...) if((x)) { AR_ERROR(__VA_ARGS__); __debugbreak(); }

#define BIND_EVENT_FN(x) std::bind(x, this, std::placeholders::_1)

namespace Arrow {

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

}