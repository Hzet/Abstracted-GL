template <typename T>
T& application::get_resource()
{
	static auto& app = get_instance();
	auto* ptr = app.m_resources[resource_type_uid::get_id<T>() - 1u].get();
	auto& result = *reinterpret_cast<T*>(ptr);

	return result;
}

template <typename T>
void application::add_resource()
{
	auto id_resource_type = resource_type_uid::get_id<T>();
	m_resources.push_back(std::make_unique<T>());
}