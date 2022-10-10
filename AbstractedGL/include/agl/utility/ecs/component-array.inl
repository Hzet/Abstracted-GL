template <typename T>
template <typename... Args>
T& component_array<T>::attach(const entity_uid &id_entity, Args&&... args)
{
	m_count++;

	m_active_entities[get_index(id_entity)] = true;
	m_components[get_index(id_entity)] = { std::forward<Args>(args)... };

	return m_components[get_index(id_entity)];
}

template <typename T>
T& component_array<T>::attach(const entity_uid &id_entity)
{
	m_count++;

	m_active_entities[get_index(id_entity)] = { };
	m_active_entities[get_index(id_entity)] = true;

	return m_components[get_index(id_entity)];
}

template <typename T>
void component_array<T>::detach(const entity_uid &id_entity)
{
	m_count--;

	m_components[get_index(id_entity)].~T();
	m_active_entities[get_index(id_entity)] = false;
}

template <typename T>
T& component_array<T>::get(const entity_uid &id_entity)
{
	AGL_CORE_ASSERT(m_active_entities[get_index(id_entity)] == true, "Component [{}] is not attached to this entity [{}]", TComponentTypeUID<T>::value(), id_entity);

	return m_components[get_index(id_entity)];
}

template <typename T>
const T& component_array<T>::get(const entity_uid &id_entity) const
{
	AGL_CORE_ASSERT(m_active_entities[get_index(id_entity)] == true, "Component [{}] is not attached to this e [{}]", TComponentTypeUID<T>::value(), id_entity);

	return m_components[get_index(id_entity)];
}

template <typename T>
std::uint64_t component_array<T>::get_index(const entity_uid &id_entity) const
{
	AGL_CORE_ASSERT(id_entity != entity_uid::INVALID, "Invalid id_entity");

	return id_entity - 1ul;
}

template <typename T>
void component_array<T>::on_entity_destroy(const entity_uid &id_entity)
{
	detach(id_entity);
}