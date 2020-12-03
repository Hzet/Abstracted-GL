#include "core.hpp"

namespace agl
{
	std::unordered_map<std::string, std::uint64_t> CProfilerClock::Clocks_ = {};

	const std::unordered_map<std::string, std::uint64_t>& CProfilerClock::GetClocks()
	{
		return Clocks_;
	}

	CProfilerClock::CProfilerClock(std::string &&callerName)
		: name_(std::move(callerName)),
		myClock_()
	{
	}

	CProfilerClock::~CProfilerClock()
	{
		Clocks_[name_] += myClock_.count();
	}
}