#pragma once
#include <chrono>

#include "agl/core/misc/timestep.hpp"

namespace agl
{
	class timer
	{
	public:
		timer();

		void start();
		void pause();
		void unpause();
		void reset();

		timestep elapsed() const;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_pause_begin;		
	};
}
