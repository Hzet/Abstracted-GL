template <typename TData, typename TComponent>
void group_uniform::add_uniform()
{
	auto& groups = get_groups();
	const auto id_uniform_type = TUniformDataTypeUID<TData>::value();
	const auto id_component_type = TComponentTypeUID<TComponent>::value();
	const auto index = get_index(id_uniform_type);

	if (groups.size() < id_uniform_type)
		groups.push_back({});

	auto &group = groups[index];
	group.push_back(std::make_unique<uniform_wrapper<TData, TComponent>>());

}