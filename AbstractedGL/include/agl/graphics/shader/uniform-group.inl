template <typename TData>
const group_uniform& group_uniform::get_group()
{
	return get_manager().get_group(TUniformDataTypeUID<TData>::value());
}



template <typename TData, typename TComponent>
void group_uniform::manager::add_uniform()
{
	const auto id_uniform_data_type = TUniformDataTypeUID<TData>::value();
	const auto id_component_type = TComponentTypeUID<TComponent>::value();
	const auto index = get_index(id_uniform_data_type);

	if (m_groups.size() <= id_uniform_data_type)
		m_groups.push_back({});

	auto &group = m_groups[index];
	group.m_prototypes.push_back(std::make_unique<uniform_wrapper<TData, TComponent>>());

}

template <typename TData, typename TComponent>
void group_uniform::add_uniform()
{
	get_manager().add_uniform<TData, TComponent>();
}