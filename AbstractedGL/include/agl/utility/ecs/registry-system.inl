template <typename TGroupName, typename T>
bool registry_system::register_system()
{
	auto &Groups = get_groups_tmp();

	const auto id_group = group_type_uid::get_id<TGroupName>();

	auto found = Groups.find(id_group);

	if (found != Groups.end())
		found->second.add_system<T>();
	else
	{
		group<TGroupName> group;
		group.add_system<T>();

		Groups.emplace(std::make_pair(group.getGroupUID(), std::move(group)));
	}

	return true;
}

template <typename TPrev, typename TNext> 
bool registry_system::order_after()
{
	auto &order = get_order_tmp();
	order.insert_after(group_type_uid::get_id<TPrev>(), group_type_uid::get_id<TNext>());

	return true;
}

template <typename TPrev, typename TNext> 
bool registry_system::order_before()
{
	auto &order = get_order_tmp();
	order.insert_before(group_type_uid::get_id<TPrev>(), group_type_uid::get_id<TNext>());

	return true;
}

template <typename TPrev, typename TNext, typename... TGroups> 
bool registry_system::order()
{
	order_impl<TPrev, TNext, TGroups...>(std::make_index_sequence<sizeof...(TGroups) + 1>{ });

	return true;
}

template <typename... TGroups, std::uint64_t... Sequence>
void registry_system::order_impl(std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<TGroups...>;

	((order_after<std::tuple_element_t<Sequence, TTuple>, std::tuple_element_t<Sequence + 1, TTuple>>()), ...);
}