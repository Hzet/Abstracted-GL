template <typename TData,typename... TComponents>
bool register_uniform<TData, TComponents...>::register_type()
{
	if constexpr (sizeof...(TComponents) > 0)
		register_type_impl(std::make_index_sequence<sizeof...(TComponents)>{ });
	else
		group_uniform::add_uniform<TData, void>();

	return true;
}

template <typename TData, typename... TComponents>
template <std::uint64_t... Sequence>
void register_uniform<TData, TComponents...>::register_type_impl(std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<TComponents...>;
	
	((group_uniform::add_uniform<TData, std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename TData, typename... TComponents>
void register_uniform<TData, TComponents...>::register_me() const
{
	register_uniform::s_registered;
}

template <typename TData, typename... TComponents>
bool register_uniform<TData, TComponents...>::s_registered = register_type();
