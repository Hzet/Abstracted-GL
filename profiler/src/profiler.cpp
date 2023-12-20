#include "profiler/profiler.hpp"

namespace agl
{
namespace profiler
{
extern profiler g_profiler = profiler();

int profiler::create(std::string const& name);
	void profiler::begin_measurement(int index);
	void profiler::end_measurement(int index);
	std::vector<profile> const& profiler::get_profiles() const;

}
}