#include "agl/utility/ecs/registry.hpp"

#include <iostream>

namespace agl
{
	std::unordered_map<std::uint64_t, group_base>& registry_system::get_groups_tmp()
	{
		static auto groups = std::unordered_map<std::uint64_t, group_base>{};

		return groups;
	}

	ordered_list<std::uint64_t>& agl::registry_system::get_order_tmp()
	{
		static auto order = ordered_list<std::uint64_t>{};

		return order;
	}

	void registry_system::order_groups()
	{
		auto &Groups = get_groups_tmp();
		auto &order = get_order_tmp();

		order.order();
		m_groups.reserve(Groups.size());

		auto insert = [&](const auto &index)
		{
			auto found = Groups.find(index);

			if (found == Groups.end())
				return;

			m_groups.push_back(std::move(found->second));
			Groups.erase(found);
		};

		if (!Groups.empty())
			for (auto &m : Groups)
				m_groups.push_back(std::move(m.second));

		Groups.clear();
		order.clear();
	}

	registry_system::registry_system(registry &reg)
	{
		order_groups();

		for (auto& v : m_groups)
			v.init(reg);
	}

	void registry_system::update(registry &reg)
	{
		for (auto &v : m_groups)
			v.update(reg);
	}
}