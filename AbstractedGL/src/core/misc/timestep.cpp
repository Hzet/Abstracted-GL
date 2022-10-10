#include "core/misc/timestep.hpp"

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

	double timestep::hours() const
	{
		return minutes() / 60.0;
	}

	double timestep::minutes() const
	{
		return seconds() / 60.0;
	}

	double timestep::seconds() const
	{
		return milliseconds() / 1000.0;
	}

	double timestep::milliseconds() const
	{
		return nanoseconds() / 1000000.0;
	}

	double timestep::nanoseconds() const
	{
		return m_nanoseconds;
	}
}