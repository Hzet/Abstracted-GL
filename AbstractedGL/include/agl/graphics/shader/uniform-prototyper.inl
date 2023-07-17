template <typename TName, typename TComponent>
void uniform_prototyper::add_prototype()
{
	auto& groups = get_groups();
	const auto id_uniform_type = uniform_type_uid::get_id<TName>();
	const auto id_component_type = component_type_uid::get_id<TComponent>();
	const auto index = get_index(id_uniform_type);

	if (groups.size() < id_uniform_type)
		groups.push_back({});

	auto &group = groups[index];
	group.push_back(std::make_unique<uniform_wrapper<TName, TComponent>>());

}