#include "agl/core/misc/timestep.hpp"

namespace agl
{
	timestep::timestep()
		: m_nanoseconds(0.0)
	{
	}

	timestep::timestep(std::uint64_t nanoseconds)
		: m_nanoseconds(nanoseconds)
	{
	}

	float timestep::hours() const
	{
		return minutes() / 60.f;
	}

	float timestep::minutes() const
	{
		return seconds() / 60.f;
	}

	float timestep::seconds() const
	{
		return milliseconds() / 1000.f;
	}

	float timestep::milliseconds() const
	{
		return nanoseconds() / 1000000.f;
	}

	float timestep::nanoseconds() const
	{
		return m_nanoseconds;
	}
}