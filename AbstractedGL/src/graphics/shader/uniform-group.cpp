#include "graphics/shader/uniform-group.hpp"
#include "graphics/shader/uniform-base.hpp"

namespace agl
{
	const group_uniform& group_uniform::get_group(uniform_data_type_uid id_uniform_data_type)
	{
		return get_manager().get_group(id_uniform_data_type);
	}

	std::uint64_t group_uniform::get_count() const
	{
		return m_prototypes.size();
	}

	const uniform_base& group_uniform::operator[](std::uint64_t index) const
	{
		return m_prototypes[index]->get_uniform();
	}

	std::unique_ptr<uniform_base> group_uniform::get_uniform(component_type_uid id_component_type, uniform_base *dataSource /*= nullptr*/) const
	{
		for (const auto &v : m_prototypes)
			if (v->get_uniform().get_component_type_uid() == id_component_type)
				return v->clone(dataSource);

		return nullptr;
	}

	group_uniform::manager& group_uniform::get_manager()
	{
		static auto result = manager{};

		return result;
	}

	group_uniform& group_uniform::manager::get_group(uniform_data_type_uid id_uniform_data_type)
	{
		return m_groups[get_index(id_uniform_data_type)];
	}

	std::uint64_t group_uniform::manager::get_index(uniform_data_type_uid id_uniform_data_type)
	{
		return id_uniform_data_type - 1ul;
	}
}