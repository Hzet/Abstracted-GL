#include "utility/ecs/component-array-base.hpp"

namespace agl
{
	std::uint64_t component_array_base::get_count() const
	{
		return m_count;
	}
}