
template <class... Args>
template <std::size_t I>
constexpr void CTupleBufferBase<Args...>::CheckRange()
{
	if constexpr (I >= sizeof...(Args))
		static_assert(false, "Buffer index out of bounds!");
}

template <class... Args>
constexpr std::size_t CTupleBufferBase<Args...>::GetStrideCount()
{
	return sizeof...(Args);
}

template <class... Args>
constexpr std::size_t CTupleBufferBase<Args...>::GetStrideSize()
{
	return GetElementOffset<sizeof...(Args)>();
}

template <class... Args>
template <std::size_t I>
constexpr std::size_t CTupleBufferBase<Args...>::GetElementSize()
{
	if constexpr (I < sizeof...(Args))
		return sizeof(std::tuple_element_t<I, std::tuple<Args...>>);
	else
		return 0u;
}

template <class... Args>
template <std::size_t I>
constexpr std::size_t CTupleBufferBase<Args...>::GetElementOffset()
{
	return GetElementOffset_impl<I>() - GetElementSize<I>();
}

template <class... Args>
template <std::size_t I>
constexpr std::size_t CTupleBufferBase<Args...>::GetElementOffset_impl()
{
	if constexpr (I == 0u)
		return GetElementSize<I>();
	else
		return GetElementSize<I>() + GetElementOffset_impl<I - 1u>();
}

template <class... Args>
template <std::size_t I>
void CTupleBufferBase<Args...>::DestructElement(std::byte * const data)
{
	CheckRange<I>();

	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	if constexpr (std::is_destructible_v<type>)
		reinterpret_cast<type*>(data + GetElementOffset<I>())->~type();
}

template <class... Args>
template <std::size_t I>
void CTupleBufferBase<Args...>::ConstructElement(std::byte * const data)
{
	CheckRange<I>();

	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	new(reinterpret_cast<type*>(data + GetElementOffset<I>())) type();
}

template <class... Args>
template <std::size_t I>
void CTupleBufferBase<Args...>::DestructAll(std::byte * const data)
{
	CheckRange<I>();

	DestructElement<I>(data);

	if constexpr (I + 1u < sizeof...(Args))
		DestructAll<I + 1u>(data);
}

template <class... Args>
template <std::size_t I>
void CTupleBufferBase<Args...>::ConstructAll(std::byte * const data)
{
	CheckRange<I>();

	ConstructElement<I>(data);

	if constexpr (I + 1u < sizeof...(Args))
		ConstructAll<I + 1u>(data);
}

template <class... Args>
template <std::size_t I, class U>
void CTupleBufferBase<Args...>::ConstructElementValue(std::byte * const data, U &&value)
{
	CheckRange<I>();

	using type = std::remove_reference_t<U>;

	if constexpr (std::is_move_constructible_v<U> || std::is_copy_constructible_v<U>)
		new(reinterpret_cast<type*>(data + GetElementOffset<I>())) type(value);
	else
		static_assert(false, "Type U is not constructible from a value");
}

template <class... Args>
void CTupleBufferBase<Args...>::ConstructValueAll(std::byte * const data, Args&&... elems)
{
	ConstructValueAll_impl(data, std::forward_as_tuple(std::forward<Args>(elems)...), std::make_index_sequence<sizeof...(Args)>{});
}


template <class... Args>
template <class Tuple, std::size_t... Sequence>
void CTupleBufferBase<Args...>::ConstructValueAll_impl(std::byte * const data, Tuple &&t, std::index_sequence<Sequence...>)
{
	(ConstructElementValue<Sequence>(data, std::get<Sequence>(t)), ...);
}

template <class... Args>
template <std::size_t I>
auto * const  CTupleBufferBase<Args...>::GetPointer(std::byte * const data)
{
	CheckRange<I>();

	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	return reinterpret_cast<type*>(data + GetElementOffset<I>());
}

template <class... Args>
template <std::size_t I>
auto const * const CTupleBufferBase<Args...>::GetPointer(std::byte const * const data)
{
	CheckRange<I>();

	using type = std::add_const_t<std::tuple_element_t<I, std::tuple<Args...>>>;

	return reinterpret_cast<type*>(data + GetElementOffset<I>());
}
