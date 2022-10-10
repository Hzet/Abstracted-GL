#pragma once
#include <chrono>
#include <cstdint>

namespace agl
{
	class timestep
	{
	public:
		timestep();
		timestep(std::uint64_t nanoseconds);

		double hours() const;
		double minutes() const;
		double seconds() const;
		double milliseconds() const;
		double nanoseconds() const;

	private:
		std::uint64_t m_nanoseconds;
	};
}

