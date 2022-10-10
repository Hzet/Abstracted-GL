template <typename... Args>
registry_component_base::TComponent<Args...> registry_component_base::get(const entity_uid &id_entity)
{
	if constexpr (sizeof...(Args) == 1)
		return get_array<std::tuple_element_t<0, std::tuple<Args...>>>().get(id_entity);
	else
		return get_component_impl<Args...>(id_entity, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
std::tuple<Args&...> registry_component_base::get_component_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	return {
		(get_array<std::tuple_element_t<Sequence, TTuple>>().get(id_entity))...
	};
}

template <typename T, typename... Args>
T& registry_component_base::attach_component(const entity_uid &id_entity, Args&&... args)
{
	return get_array<T>().attach(id_entity, std::forward<Args>(args)...);
}

template <typename... Args>
registry_component_base::TComponent<Args...> registry_component_base::attach_component(const entity_uid &id_entity)
{
	if constexpr (sizeof...(Args) == 1)
		return get_array<Args...>().attach(id_entity);
	else
		return attach_component_impl<Args...>(id_entity, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
std::tuple<Args&...> registry_component_base::attach_component_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	std::tuple<Args&...> result{ 
		(get_array<std::tuple_element_t<Sequence, TTuple>>().attach(id_entity))... 
	};

	return result;
}

template <typename... Args>
void registry_component_base::detach_component(const entity_uid &id_entity)
{
	detach_component_impl<Args...>(id_entity, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
void registry_component_base::detach_component_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	((get_array_base<std::tuple_element_t<Sequence, TTuple>>()->on_entity_destroy(id_entity)), ...);
}

template <typename... Args>
std::tuple<component_array<Args>&...> registry_component_base::get_arrays()
{
	return get_arrays_impl<Args...>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
std::tuple<component_array<Args>&...> registry_component_base::get_arrays_impl(std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	return {
		(get_array<std::tuple_element_t<Sequence, TTuple>>())...
	};
}

template <typename T>
component_array<T>& registry_component_base::get_array()
{
	const auto index = TComponentTypeUID<T>::value() - 1ul;

	auto &componentArray = m_arrays[index];

	if (componentArray == nullptr)
		componentArray = std::make_unique<component_array<T>>();

	return *reinterpret_cast<component_array<T>*>(componentArray.get());
}

template <typename T>
component_array_base* registry_component_base::get_array_base()
{
	return m_arrays[TComponentTypeUID<T>::value() - 1ul].get();
}