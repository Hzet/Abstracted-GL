#include "graphics/shader/uniform-group.hpp"
#include "graphics/shader/uniform-base.hpp"
#include "system/debug/assert.hpp"

namespace agl
{
	std::unique_ptr<uniform_base> group_uniform::get_uniform(uniform_type_uid id_uniform, component_type_uid id_component_type, uniform_base *dataSource /*= nullptr*/)
	{
		auto const& groups = get_groups();

		for (const auto &v : groups[get_index(id_uniform)])
			if (v->get_uniform().get_component_type_uid() == id_component_type)
				return v->clone(dataSource);

		AGL_CORE_ASSERT(false, "Uniform {} is not capable of handling component {}", uniform_type_uid::get_name(id_uniform), component_type_uid::get_name(id_component_type));
		return nullptr;
	}

	std::uint64_t group_uniform::get_index(uniform_type_uid id_uniform_type)
	{
		return id_uniform_type - 1ul;
	}

	std::vector<std::vector<std::unique_ptr<uniform_wrapper_base>>>& group_uniform::get_groups()
	{
		static auto result = std::vector<std::vector<std::unique_ptr<uniform_wrapper_base>>>{};

		return result;
	}
}