template <typename T, typename... Args> 
T& registry::attach(const entity_uid &id_entity, Args&&... args)
{
	this->get_signature(id_entity).attach_type<T>();
	
	return this->attach_component<T>(id_entity, std::forward<Args>(args)...);
}

template <typename... Args>
registry::TComponent<Args...> registry::attach(const entity_uid &id_entity)
{
	this->get_signature(id_entity).attach_type<Args...>();

	return this->attach_component<Args...>(id_entity);
}

template <typename... Args> 
void registry::detach(const entity_uid &id_entity)
{
	this->get_signature(id_entity).detach_type<Args...>();
	this->detach_component<Args...>(id_entity);
}

template <typename... Args>
view<Args...> registry::strict_view()
{
	auto result = view<Args...>{ this->get_arrays_ptr<Args...>() };

	result.track(entities_matching(signature::create<Args...>()));

	return result;
}

template <typename... Args> 
view<Args...> registry::inclusive_view()
{
	auto result = view<Args...>{ this->get_arrays_ptr<Args...>() };

	result.track(entities_including(signature::create<Args...>()));

	return result;
}
