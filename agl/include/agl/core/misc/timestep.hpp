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

		float hours() const;
		float minutes() const;
		float seconds() const;
		float milliseconds() const;
		float nanoseconds() const;

	private:
		std::uint64_t m_nanoseconds;
	};
}

