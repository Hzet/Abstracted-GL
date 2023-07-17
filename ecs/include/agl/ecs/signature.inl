template <typename TComponent>
std::uint64_t signature::get_index()
{
	return component_type_uid::get_id<TComponent>() - 1ul;
}

template<typename... Args>
signature signature::create()
{
	auto sig = signature{};
	sig.attach_type<Args...>();

	return sig;
}

template <typename... Args> 
bool signature::has_type() const
{
	return has_type_impl<std::tuple<Args...>>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename TTuple, std::uint64_t... Sequence>
bool signature::has_type_impl(std::index_sequence<Sequence...>) const
{
	return (... && (m_signature[get_index<std::tuple_element_t<Sequence, TTuple>>()] == true));
}

template <typename... Args>
void signature::attach_type()
{
	attach_type_impl<std::tuple<Args...>>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename TTuple, std::uint64_t... Sequence>
void signature::attach_type_impl(std::index_sequence<Sequence...>)
{
	((attach_type_impl<std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename T>
void signature::attach_type_impl()
{
	const auto index = get_index<T>();
	
	if (m_peak < static_cast<std::int64_t>(index))
		m_peak = index;

	m_signature.set(index, true);
}

template <typename... Args> 
void signature::detach_type()
{
	detach_type_impl<std::tuple<Args...>>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename TTuple, std::uint64_t... Sequence>
void signature::detach_type_impl(std::index_sequence<Sequence...>)
{
	((detach_type_impl<std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename T>
void signature::detach_type_impl()
{
	const auto index = get_index<T>();
	
	// update the 'm_peak'
	if (get_count() == 1ul)
		m_peak = -1;
	else if (m_peak == index)
		for (auto i = m_peak - 1; i > 0; i--)
			if (m_signature[i] == true)
				m_peak = i;

	m_signature.set(index, false);
}

