
template <class... Args>
template <std::size_t I>
constexpr void tuple_buffer_base<Args...>::check_range()
{
	if constexpr (I >= sizeof...(Args))
		static_assert(false, "Buffer index out of bounds!");
}

template <class... Args>
constexpr std::size_t tuple_buffer_base<Args...>::get_stride_count()
{
	return sizeof...(Args);
}

template <class... Args>
constexpr std::size_t tuple_buffer_base<Args...>::get_stride_size()
{
	return get_element_offset<sizeof...(Args)>();
}

template <class... Args>
template <std::size_t I>
constexpr std::size_t tuple_buffer_base<Args...>::get_element_size()
{
	if constexpr (I < sizeof...(Args))
		return sizeof(std::tuple_element_t<I, std::tuple<Args...>>);
	else
		return 0u;
}

template <class... Args>
template <std::size_t I>
constexpr std::size_t tuple_buffer_base<Args...>::get_element_offset()
{
	return get_element_offset_impl<I>() - get_element_size<I>();
}

template <class... Args>
template <std::size_t I>
constexpr std::size_t tuple_buffer_base<Args...>::get_element_offset_impl()
{
	if constexpr (I == 0u)
		return get_element_size<I>();
	else
		return get_element_size<I>() + get_element_offset_impl<I - 1u>();
}

template <class... Args>
template <std::size_t I>
void tuple_buffer_base<Args...>::destruct_element(std::byte * const data)
{
	check_range<I>();

	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	if constexpr (std::is_destructible_v<type>)
		reinterpret_cast<type*>(data + get_element_offset<I>())->~type();
}

template <class... Args>
template <std::size_t I>
void tuple_buffer_base<Args...>::construct_element(std::byte * const data)
{
	check_range<I>();

	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	new(reinterpret_cast<type*>(data + get_element_offset<I>())) type();
}

template <class... Args>
template <std::size_t I>
void tuple_buffer_base<Args...>::destruct_all(std::byte * const data)
{
	check_range<I>();

	destruct_element<I>(data);

	if constexpr (I + 1u < sizeof...(Args))
		destruct_all<I + 1u>(data);
}

template <class... Args>
template <std::size_t I>
void tuple_buffer_base<Args...>::construct_all(std::byte * const data)
{
	check_range<I>();

	construct_element<I>(data);

	if constexpr (I + 1u < sizeof...(Args))
		construct_all<I + 1u>(data);
}

template <class... Args>
template <std::size_t I, class U>
void tuple_buffer_base<Args...>::construct_element_value(std::byte * const data, U &&value)
{
	check_range<I>();

	using type = std::remove_reference_t<U>;

	if constexpr (std::is_move_constructible_v<U> || std::is_copy_constructible_v<U>)
		new(reinterpret_cast<type*>(data + get_element_offset<I>())) type(value);
	else
		static_assert(false, "Type U is not constructible from a value");
}

template <class... Args>
void tuple_buffer_base<Args...>::construct_value_all(std::byte * const data, Args&&... elems)
{
	construct_value_all_impl(data, std::forward_as_tuple(std::forward<Args>(elems)...), std::make_index_sequence<sizeof...(Args)>{});
}


template <class... Args>
template <class Tuple, std::size_t... Sequence>
void tuple_buffer_base<Args...>::construct_value_all_impl(std::byte * const data, Tuple &&t, std::index_sequence<Sequence...>)
{
	(construct_element_value<Sequence>(data, std::get<Sequence>(t)), ...);
}

template <class... Args>
template <std::size_t I>
auto * const  tuple_buffer_base<Args...>::get_pointer(std::byte * const data)
{
	check_range<I>();

	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	return reinterpret_cast<type*>(data + get_element_offset<I>());
}

template <class... Args>
template <std::size_t I>
auto const * const tuple_buffer_base<Args...>::get_pointer(std::byte const * const data)
{
	check_range<I>();

	using type = std::add_const_t<std::tuple_element_t<I, std::tuple<Args...>>>;

	return reinterpret_cast<type*>(data + get_element_offset<I>());
}
