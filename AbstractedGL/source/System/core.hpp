#pragma once 

#include <chrono>
#include <unordered_map>
#include "log.hpp"

#define AGL_PROFILE() \
CProfilerClock AGL_PROFILE_VARIABLE(__FILE__ + ' - ' + __FUNCTION__ + ' - ' + __LINE__); \

namespace agl
{
	class CProfilerClock
	{
	public:
		CProfilerClock(std::string &&callerName);
		~CProfilerClock();

		static const std::unordered_map<std::string, std::uint64_t>& GetClocks();
	private:
		static std::unordered_map<std::string, std::uint64_t> Clocks_;

		const std::string name_;
		const std::chrono::milliseconds myClock_;
	};
}