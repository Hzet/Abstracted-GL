template <typename... Args>
bool has(const entity_uid &id_entity)
{
	return get_entity(id_entity).has_component<Args...>();
}