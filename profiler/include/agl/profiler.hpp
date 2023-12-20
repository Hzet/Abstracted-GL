#pragma once

#ifdef AGL_ENABLE_PROFILING
#include <string>
#include <vector>
#include "agl/debug/debug.hpp"

namespace agl
{
namespace profiler
{
	struct profile
	{
		std::string name;
		double time = 0;
	};

	class profiler
	{
	public:
		profiler() = default;
		profiler(profiler&&) = delete;
		profiler(profiler const&) = delete;
		profiler& operator=(profiler&&) = delete;
		profiler& operator=(profiler const&) = delete;
		
		int create(std::string const& name);
		void begin_measurement(int index);
		void end_measurement(int index);
		std::vector<profile> const& get_profiles() const;

	private:
		std::vector<profile> m_profiles;
	};

	extern profiler g_profiler;
}
}


#define AGL_BEGIN_PROFILER(name) \
	static auto const profiler_index = agl::profiler::g_profiler.create(name); \
	agl::profiler::g_profiler.begin_measurement(profiler_index);

#define AGL_END_PROFILER() \
	agl::profiler::g_profiler.end_measurement(profiler_index);


#else

#endif