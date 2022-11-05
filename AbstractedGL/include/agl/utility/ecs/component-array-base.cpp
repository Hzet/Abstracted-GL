#include "agl/utility/ecs/component-array-base.hpp"

namespace agl
{
	component_array_base::component_array_base()
		: m_changed{ true }
		, m_count{ 0 }
	{
	}

	bool component_array_base::has_changed() const
	{
		return m_changed;
	}
		
	std::uint64_t component_array_base::get_count() const
	{
		return m_count;
	}
}