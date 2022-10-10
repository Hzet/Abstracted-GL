template <typename... Args>
registry_component_base::TComponent<Args...> entity::get_component() const
{
	return m_registry->get<Args...>(m_id);
}

template <typename... Args>
bool entity::has_component() const
{
	return m_signature.has_type<Args...>();
}

template <typename... Args> 
void entity::detach_component()
{
	m_signature.detach_type<Args...>();
	m_registry->detach<Args...>(*this);
}

template <typename T, typename... Args> 
T& entity::attach_component(Args&&... args)
{
	m_signature.attach_type<T>();
	
	return m_registry->attach<T>(*this, std::forward<Args>(args)...);
}

template <typename... Args>
registry::TComponent<Args...> agl::entity::attach_component()
{
	m_signature.attach_type<Args...>();
	
	return m_registry->attach<Args...>(*this);
}