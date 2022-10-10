template <class... Args>
tuple_buffer<Args...>::tuple_buffer() noexcept
{}
/*

template <class... Args>
CTupleBuffer<Args...>::CTupleBuffer(Args&&... elems)
{
	push_back(std::forward<Args>(elems)...);
}
*/

template <class... Args>
tuple_buffer<Args...>::~tuple_buffer()
{
	clear();
}

template <class... Args>
void tuple_buffer<Args...>::push_back(Args&&... elems)
{
	m_data.resize((get_count() + 1u) * get_stride_size());

	this->construct_value_all(get_storage_pointer<0>(get_count() - 1u), std::forward<Args>(elems)...);
}

template <class... Args>
void tuple_buffer<Args...>::clear()
{
	const auto size = m_data.size();
	auto * const data = m_data.data();

	for (std::size_t i = 0u; i < size; i += get_stride_size())
		this->destruct_all(data + i);

	m_data.clear();
}

template <class... Args>
void tuple_buffer<Args...>::resize(std::size_t count)
{
	if (count == get_count())
		return;
	else if (count == 0u)
	{
		clear();
		return;
	}

	const auto newSize = count * get_stride_size();
	const auto oldSize = m_data.size();

	if (count < get_count())
	{
		auto * const data = m_data.data();
		for (std::size_t i = newSize; i < oldSize; i += get_stride_size())
			this->destruct_all(data + i);

		m_data.resize(newSize);
	}
	else if (count > get_count())
	{
		m_data.resize(newSize);

		auto * const data = m_data.data();
		for (std::size_t i = oldSize; i < newSize; i += get_stride_size())
			this->construct_all(data + i);
	}
}


template <class... Args>
std::size_t tuple_buffer<Args...>::get_size() const
{
	return m_data.size();
}

template <class... Args>
std::size_t tuple_buffer<Args...>::get_count() const
{
	return get_size() / get_stride_size();
}

template <class... Args>
std::size_t tuple_buffer<Args...>::get_stride_size() const
{
	return this->m_stride_size;
}

template <class... Args>
std::size_t tuple_buffer<Args...>::get_stride_count() const
{
	return this->m_stride_count;
}

template <class... Args>
template <std::size_t I>
auto& tuple_buffer<Args...>::get(std::size_t index)
{
	this->check_range<I>();

	return *get_pointer<I>(index);
}

template <class... Args>
template <std::size_t I>
const auto& tuple_buffer<Args...>::get(std::size_t index) const
{
	this->check_range<I>();

	return *get_pointer<I>(index);
}

template <class... Args>
std::byte const * const tuple_buffer<Args...>::get_data() const
{
	return m_data.data();
}

template <class... Args>
template <std::size_t I>
auto * const tuple_buffer<Args...>::get_pointer(std::size_t index)
{
	return this->get_pointer<I>(m_data.data() + get_stride_size() * index);
}

template <class... Args>
template <std::size_t I>
auto const * const tuple_buffer<Args...>::get_pointer(std::size_t index) const
{
	return this->get_pointer<I>(m_data.data() + get_stride_size() * index);
}

template <class... Args>
template <std::size_t I>
std::byte * const tuple_buffer<Args...>::get_storage_pointer(std::size_t index)
{
	return m_data.data() + this->get_element_offset<I>() + get_stride_size() * index;
}

template <class... Args>
template <std::size_t I>
std::byte const * const tuple_buffer<Args...>::get_storage_pointer(std::size_t index) const
{
	return m_data.data() + this->get_element_offset<I>() + get_stride_size() * index;
}