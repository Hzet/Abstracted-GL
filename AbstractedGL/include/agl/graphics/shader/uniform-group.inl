template <typename TName, typename TComponent>
void uniform_prototyper::add_prototype()
{
	auto const id_uniform = TUniformDataTypeUID<TName>::value();

	if (get_groups().size() < id_uniform)
		get_groups().resize(get_groups().size() + 1);

	auto &group = get_groups()[get_group_index(id_uniform)];
	group.prototypes.push_back(std::make_unique<uniform_wrapper<TName, TComponent>>());
}



/*
template <typename TName>
const group_uniform& group_uniform::get_group()
{
	return get_manager().get_group(TUniformDataTypeUID<TName>::value());
}



template <typename TName, typename TComponent>
void group_uniform::manager::add_uniform()
{
	const auto id_uniform_type = TUniformDataTypeUID<TName>::value();
	const auto id_component_type = TComponentTypeUID<TComponent>::value();
	const auto index = get_index(id_uniform_type);

	if (m_groups.size() <= id_uniform_type)
		m_groups.push_back({});

	auto &group = m_groups[index];
	group.m_prototypes.push_back(std::make_unique<uniform_wrapper<TName, TComponent>>());

}

template <typename TName, typename TComponent>
void group_uniform::add_uniform()
{
	get_manager().add_uniform<TName, TComponent>();
}*/