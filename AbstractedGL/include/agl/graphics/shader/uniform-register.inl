template <typename TName, typename... TComponents>
uniform_register<TName, TComponents...>::uniform_register(std::string const& name)
	: uniform_base{ name }
{
}

template <typename TName,typename... TComponents>
bool uniform_register<TName, TComponents...>::register_type()
{
	register_type_impl(std::make_index_sequence<sizeof...(TComponents)>{ });
	return true;
}

template <typename TName, typename... TComponents>
template <std::uint64_t... Sequence>
void uniform_register<TName, TComponents...>::register_type_impl(std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<TComponents...>;
	
	((uniform_prototyper::add_prototype<TName, std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename TName, typename... TComponents>
void uniform_register<TName, TComponents...>::register_me() const
{
	uniform_register::s_registered;
}

template <typename TName, typename... TComponents>
bool uniform_register<TName, TComponents...>::s_registered = uniform_register<TName, TComponents...>::register_type();
