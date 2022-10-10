#pragma once
#include <unordered_map>
#include <vector>

#include "utility/ecs/group.hpp"
#include "utility/ordered-list.hpp"

namespace agl
{
	class registry_system
	{
	public:
		struct misc_group {};

	public:
		template <typename TPrev, typename TNext> static bool order_after();
		template <typename TPrev, typename TNext> static bool order_before();
		template <typename TPrev, typename TNext, typename... TGroups> static bool order();

	protected:
		registry_system(registry &reg);
		virtual ~registry_system() = default;

		void update(registry &reg);

	private:
		template <typename TGroupName, typename TDerived> friend class system_object;
		template <typename TGroupName, typename T> static bool system();
		template <typename... TGroups, std::uint64_t... Sequence> static void order_impl(std::index_sequence<Sequence...>);
		static std::unordered_map<std::uint64_t, group_base>& get_groups_tmp();
		static ordered_list<std::uint64_t>& get_order_tmp();

	private:
		void order_groups();

		std::vector<group_base> m_groups;
	};

#include "utility/ecs/registry-system.inl"
}