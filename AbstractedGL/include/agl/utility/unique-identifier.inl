template <typename T, std::uint64_t Size>
std::uint64_t TUID<T, Size>::GetRefCount(const TUID &uid)
{
	return get_manager().get_references_count(uid);
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID()
	: m_id(get_manager().create())
{
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(EInvalid)
	: m_id(INVALID)
{
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::~TUID()
{
	if(m_id != INVALID)
		get_manager().destroy(*this);
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(TUID &&other)
	: m_id(other.m_id)
{
	other.m_id = INVALID;
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(const TUID &other)
	: m_id(other.m_id)
{
	get_manager().increment(*this);
}

template <typename T, std::uint64_t Size>
TUID<T, Size>& TUID<T, Size>::operator=(TUID &&other)
{
	std::swap(m_id, other.m_id);

	return *this;
}

template <typename T, std::uint64_t Size>
TUID<T, Size>& TUID<T, Size>::operator=(const TUID &other)
{
	m_id = other.m_id;
	get_manager().increment(*this);

	return *this;
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::operator std::uint64_t() const
{
	return m_id;
}

template <typename T, std::uint64_t Size>
CUIDManager& TUID<T, Size>::get_manager()
{
	static auto result = CUIDManager{ Size };

	return result;
}