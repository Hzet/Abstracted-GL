template <typename TName>
TStaticUID<TName> TStaticUID<TName>::create()
{
	return get_manager().create();
}

template <typename TName>
TStaticUID<TName>::TStaticUID()
	: m_id(INVALID)
{
}

template <typename TName>
TStaticUID<TName>::operator std::uint64_t() const
{
	return m_id;
}

template <typename TName>
typename TStaticUID<TName>::manager& TStaticUID<TName>::get_manager()
{
	static auto result = manager{};

	return result;
}

template <typename TName>
TStaticUID<TName>::TStaticUID(std::uint64_t uid)
	: m_id(uid)
{
}

template <typename TName>
TStaticUID<TName>::manager::manager()
	: m_counter(0ul)
{
}

template <typename TName>
std::uint64_t TStaticUID<TName>::manager::create()
{
	return ++m_counter;
}