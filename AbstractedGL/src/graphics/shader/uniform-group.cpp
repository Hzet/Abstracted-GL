#include "graphics/shader/uniform-group.hpp"
#include "graphics/shader/uniform-base.hpp"

namespace agl
{
/*
	const group_uniform& group_uniform::get_group(uniform_type_uid id_uniform_type)
	{
		return get_manager().get_group(id_uniform_type);
	}

	std::uint64_t group_uniform::get_count() const
	{
		return m_prototypes.size();
	}

	const uniform_base& group_uniform::operator[](std::uint64_t index) const
	{
		return m_prototypes[index]->get_uniform();
	}

	std::unique_ptr<uniform_base> group_uniform::get_uniform(component_type_uid id_component_type, uniform_base *dataSource / *= nullptr* /) const
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

	group_uniform& group_uniform::manager::get_group(uniform_type_uid id_uniform_type)
	{
		return m_groups[get_index(id_uniform_type)];
	}

	std::uint64_t group_uniform::manager::get_index(uniform_type_uid id_uniform_type)
	{
		return id_uniform_type - 1ul;
	}*/


	std::uint64_t uniform_prototyper::get_group_index(uniform_type_uid id_uniform_type)
	{
		return id_uniform_type - 1;
	}

	std::unique_ptr<uniform_base> uniform_prototyper::get_prototype(uniform_type_uid id_uniform_type, component_type_uid id_component, uniform_base* source /*= nullptr*/)
	{
		for (const auto &v : get_groups()[get_group_index(id_uniform_type)].prototypes)
			if (v->get_uniform().get_component_type_uid() == id_component)
				return v->clone(source);

		return nullptr;
	}

	std::unique_ptr<agl::uniform_base> uniform_prototyper::get_prototype(uniform_type_uid id_uniform_type)
	{
		return get_groups()[id_uniform_type].prototypes.front()->clone();
	}

	std::vector<component_type_uid> uniform_prototyper::get_prototype_components(uniform_type_uid id_uniform_type)
	{
		auto result = std::vector<component_type_uid>{};
		auto const& group = get_groups()[get_group_index(id_uniform_type)];

		result.reserve(group.prototypes.size());
		for (auto const& ptr : group.prototypes)
			result.push_back(ptr->get_uniform().get_component_type_uid());

		return result;
	}

	std::vector<uniform_prototyper::group>& uniform_prototyper::get_groups()
	{
		auto s_groups = std::vector<group>{};

		return s_groups;
	}

}