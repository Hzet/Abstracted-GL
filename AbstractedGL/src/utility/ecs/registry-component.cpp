#include "utility/ecs/registry-component.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void registry_component_base::on_entity_destroy(const entity &e)
	{
		const auto &sig = e.get_signature();

		for (auto i = 0u; i < sig.get_count(); i++)
			if (sig[i])
				m_arrays[i]->on_entity_destroy(e);
	}

	std::uint64_t registry_component_base::get_array_count(std::uint64_t index) const
	{
		return m_arrays[index]->get_count();
	}
}

