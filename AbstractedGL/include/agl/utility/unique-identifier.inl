template <typename T, std::uint64_t Size>
std::uint64_t unique_id<T, Size>::get_reference_count(const unique_id &uid)
{
	return get_manager().get_references_count(uid);
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>::unique_id()
	: m_id(get_manager().create())
{
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>::unique_id(invalid_type)
	: m_id(INVALID)
{
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>::~unique_id()
{
	if(m_id != INVALID)
		get_manager().destroy(*this);
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>::unique_id(unique_id &&other)
	: m_id(other.m_id)
{
	other.m_id = INVALID;
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>::unique_id(const unique_id &other)
	: m_id(other.m_id)
{
	get_manager().increment(*this);
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>& unique_id<T, Size>::operator=(unique_id &&other)
{
	std::swap(m_id, other.m_id);

	return *this;
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>& unique_id<T, Size>::operator=(const unique_id &other)
{
	m_id = other.m_id;
	get_manager().increment(*this);

	return *this;
}

template <typename T, std::uint64_t Size>
unique_id<T, Size>::operator std::uint64_t() const
{
	return m_id;
}

template <typename T, std::uint64_t Size>
CUIDManager& unique_id<T, Size>::get_manager()
{
	static auto result = CUIDManager{ Size };

	return result;
}