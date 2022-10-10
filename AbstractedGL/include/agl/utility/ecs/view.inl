template <typename... Args>
view<Args...>::iterator::iterator(view<Args...> &view, std::vector<entity_uid>::iterator it)
	: m_view(view),
	m_iterator(it)
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
typename view<Args...>::iterator::reference view<Args...>::iterator::operator*()
{
	return m_view.get(*m_iterator);
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
const entity_uid& view<Args...>::iterator::get_entity_uid() const
{
	return *m_iterator;
}

template <typename... Args>
typename view<Args...>::iterator view<Args...>::begin()
{
	return view<Args...>::iterator{ *this, m_entities.begin() };
}

template <typename... Args>
typename view<Args...>::iterator view<Args...>::end()
{
	return view<Args...>::iterator{ *this, m_entities.end() };
}

template <typename... Args>
std::uint64_t view<Args...>::get_count() const 
{
	return m_entities.size();
}

template <typename... Args>
view<Args...>::view(std::tuple<component_array<Args>&...> arrays)
	: m_arrays(std::move(arrays))
{
}

template <typename... Args>
void view<Args...>::track(std::vector<entity_uid> &&entities)
{
	m_entities = std::move(entities);
}


template <typename... Args>
registry_component_base::TComponent<Args...> view<Args...>::get(const entity_uid &id_entity)
{
	return get_impl(id_entity, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args>
template <std::uint64_t... Sequence>
registry_component_base::TComponent<Args...> view<Args...>::get_impl(const entity_uid &id_entity, std::index_sequence<Sequence...>)
{
	return { (std::get<Sequence>(m_arrays).get(id_entity))... };
}