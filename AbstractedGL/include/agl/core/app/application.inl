template <typename T>
T& application::get_resource()
{
	static auto& app = get_instance();
	static const auto id_resource_type = resource_type_uid::get_id<T>();

	AGL_CORE_ASSERT(id_resource_type <= app.m_resources.size(), "Resource \"{}\" not present", resource_type_uid::get_name(id_resource_type));

	return app.m_resources[id_resource_type - 1].get<T>();
}

template <typename T>
void application::add_resource()
{
	static auto& app = get_instance();
	static const auto id_resource_type = resource_type_uid::get_id<T>();

	AGL_CORE_ASSERT(id_resource_type > app.m_resources.size(), "Resource \"{}\" already present", resource_type_uid::get_name(id_resource_type));

	app.m_resources.push_back(resource::create<T>());
}