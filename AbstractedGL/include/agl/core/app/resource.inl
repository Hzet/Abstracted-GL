template <typename T, typename... TArgs>
resource resource::create(TArgs&&... args)
{
	auto result = resource{};

	result.emplace<T>(std::forward<TArgs>(args)...);

	return result;
}

template <typename T>
T& resource::get()
{
	static const auto id_resource = resource_type_uid::get_id<T>();

	AGL_CORE_ASSERT(m_id == id_resource, "Invalid resource cast. Stored type is \"{}\" not \"{}\"", resource_type_uid::get_name(m_id), resource_type_uid::get_name(id_resource));

	return *reinterpret_cast<T*>(m_buffer.data());
}

template <typename T, typename... TArgs>
void resource::emplace(TArgs&&... args)
{
	static const auto size = sizeof(T);
	static const auto id_resource = resource_type_uid::get_id<T>();

	reset();

	m_buffer.resize(size);
	m_destructor = std::unique_ptr<resource_destructor_base>(new resource_destructor<T>());
	m_id = id_resource;

	new (&m_buffer[0]) T(std::forward<TArgs>(args)...);
}