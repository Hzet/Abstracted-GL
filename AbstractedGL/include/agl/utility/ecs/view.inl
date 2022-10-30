template <typename... Args>
view<Args...>::iterator::iterator(view<Args...> const& view, std::vector<entity_uid>::const_iterator it)
	: m_view(view)
	, m_iterator(it)
{
}

template <typename... Args>
bool view<Args...>::iterator::operator!=(const iterator &other) const
{
	return m_iterator != other.m_iterator;
}

template <typename... Args>
bool view<Args...>::iterator::operator==(const iterator &other) const
{
	return m_iterator == other.m_iterator;
}

template <typename... Args>
entity_uid view<Args...>::iterator::operator*() const
{
	return *m_iterator;
}

template <typename... Args>
entity_uid const* const view<Args...>::iterator::operator->() const
{
	return &(*m_iterator);
}

template <typename... Args>
typename view<Args...>::iterator view<Args...>::iterator::operator++(int)
{
	auto result = iterator{ *this };

	++(*this);

	return result;
}

template <typename... Args>
typename view<Args...>::iterator& view<Args...>::iterator::operator++()
{
	++m_iterator;
	return *this;
}

template <typename... Args>
view<Args...>::~view()
{
	null_arrays(std::make_index_sequence<sizeof...(Args)>{});
}

template <typename... Args>
typename view<Args...>::iterator view<Args...>::cbegin() const
{
	return view<Args...>::iterator{ *this, m_entities.cbegin() };
}

template <typename... Args>
typename view<Args...>::iterator view<Args...>::cend() const
{
	return view<Args...>::iterator{ *this, m_entities.cend() };
}

template <typename... Args>
std::uint64_t view<Args...>::get_count() const
{
	return m_entities.size();
}

template<typename ...Args>
bool agl::view<Args...>::needs_update() const
{
	return needs_update_impl(std::make_index_sequence<sizeof...(Args)>{ });
}

template<typename ...Args>
template<std::uint64_t ...Sequence>
bool agl::view<Args...>::needs_update_impl(std::index_sequence<Sequence...>) const
{
	return (... && (std::get<Sequence>(m_arrays)->has_changed()));
}

template <typename... Args>
view<Args...>::view(std::tuple<component_array<Args>*...> arrays, std::vector<entity_uid>&& entities)
	: m_arrays{ std::move(arrays) }
	, m_entities{ std::move(entities) }
{
}

template <typename... Args>
template <std::uint64_t... Sequence>
void view<Args...>::null_arrays(std::index_sequence<Sequence...>)
{
	((std::get<Sequence>(m_arrays) = nullptr), ...);
}