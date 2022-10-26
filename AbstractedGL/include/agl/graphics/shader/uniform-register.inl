template <typename TName, typename... TComponents>
register_uniform<TName, TComponents...>::register_uniform(std::string const& name)
	: uniform_base{ name }
{
}

template <typename TName, typename... TComponents>
bool register_uniform<TName, TComponents...>::register_type()
{
	register_type_impl(std::make_index_sequence<sizeof...(TComponents)>{ });

	return true;
}

template <typename TName, typename... TComponents>
template <std::uint64_t... Sequence>
void register_uniform<TName, TComponents...>::register_type_impl(std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<TComponents...>;
	
	((uniform_prototyper::add_prototype<TName, std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename TName, typename... TComponents>
void register_uniform<TName, TComponents...>::register_me() const
{
	register_uniform::s_registered;
}

template <typename TName, typename... TComponents>
bool register_uniform<TName, TComponents...>::s_registered = register_type();
