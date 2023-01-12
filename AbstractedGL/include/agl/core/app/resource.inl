template <typename TName>
resource<TName>::~resource()
{
	reset();
}

template <typename TName>
void resource<TName>::reset()
{
	if (!is_any())
		return;

	m_destructor->destruct_element(m_buffer.data());
	m_buffer.clear();
}

template <typename TName>
bool resource<TName>::is_any() const
{
	return !m_buffer.empty();
}

template <typename TName>
resource_type_uid<TName> resource<TName>::get_id() const
{
	return m_id;
}

template <typename TName>
template <typename T, typename... TArgs>
resource<TName> resource<TName>::create(TArgs&&... args)
{
	auto result = resource{};

	result.emplace<T>(std::forward<TArgs>(args)...);

	return result;
}

template <typename TName>
template <typename T>
T& resource<TName>::get()
{
	static const auto id_resource = resource_type_uid<TName>::template get_id<T>();

	AGL_CORE_ASSERT(m_id == id_resource, "Invalid resource cast. Stored type is \"{}\" not \"{}\"", resource_type_uid<TName>::get_name(m_id), resource_type_uid<TName>::get_name(id_resource));

	return *reinterpret_cast<T*>(m_buffer.data());
}

template <typename TName>
template <typename T, typename... TArgs>
void resource<TName>::emplace(TArgs&&... args)
{
	static const auto size = sizeof(T);
	static const auto id_resource = resource_type_uid<TName>::template get_id<T>();

	reset();

	m_buffer.resize(size);
	m_destructor = std::unique_ptr<resource_destructor_base<TName>>(new resource_destructor<TName, T>());
	m_id = id_resource;

	new (m_buffer.data()) T(std::forward<TArgs>(args)...);
}