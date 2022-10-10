#include "core/misc/timer.hpp"

namespace agl
{
	timer::timer()
	{
		reset();
	}

	void timer::pause()
	{
		m_pause_begin = std::chrono::high_resolution_clock::now();
	}

	void timer::unpause()
	{
		m_begin += std::chrono::high_resolution_clock::now() - m_pause_begin;
	}

	void timer::reset()
	{
		m_begin = std::chrono::high_resolution_clock::now();
	}

	timestep timer::elapsed() const
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
}