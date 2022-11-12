template <typename TInherited, typename TData>
base_type<TInherited, TData>::base_type(base_type &&other)
	: m_data(std::move(other.m_data))
{
}

template <typename TInherited, typename TData>
base_type<TInherited, TData>::base_type(const base_type &other)
	: m_data(other.m_data)
{
}

template <typename TInherited, typename TData>
template <typename... Args>
base_type<TInherited, TData>::base_type(Args&&... args)
	: m_data{  std::forward<Args>(args)...  }
{
}

template <typename TInherited, typename TData>
base_type<TInherited, TData>& base_type<TInherited, TData>::operator=(base_type &&other)
{
	m_data = std::move(other.m_data);

	return *this;
}

template <typename TInherited, typename TData>
base_type<TInherited, TData>& base_type<TInherited, TData>::operator=(const base_type &other)
{
	m_data = other.m_data;

	return *this;
}

template <typename TInherited, typename TData>
template <typename... Args>
base_type<TInherited, TData>& base_type<TInherited, TData>::operator=(Args&&... args)
{
	m_data = TData{ std::forward<Args>(args)... };

	return *this;
}

template <typename TInherited, typename TData>
base_type<TInherited, TData>::operator TData&()
{
	return m_data;
}

template <typename TInherited, typename TData>
base_type<TInherited, TData>::operator const TData&() const
{
	return m_data;
}

template <typename TInherited, typename TData>
TData* const base_type<TInherited, TData>::operator->()
{
	return &m_data;
}

template <typename TInherited, typename TData>
const TData* const base_type<TInherited, TData>::operator->() const
{
	return &m_data;
}