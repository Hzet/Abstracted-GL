template <typename T>
ordered_list<T>::element::element()
	: m_count(0ul)
{
}

template <typename T>
std::uint64_t ordered_list<T>::element::get_count() const
{
	return m_count;
}

template <typename T>
const T& ordered_list<T>::element::get_element() const
{
	return m_element;
}

template <typename T>
bool ordered_list<T>::element::has_element(T element) const
{
	for (const auto &v : m_sub_elements)
		if (v.has_element(element))
			return true;
	return false;
}

template <typename T>
bool ordered_list<T>::element::insert_after(T prev, T next)
{
	m_count++;

	if (m_count - 1ul == 0ul)
	{
		m_element = prev;
		m_sub_elements.push_back(next);
		m_count++;

		return true;
	}

	if (get_element() == prev)
	{
		m_sub_elements.push_back(next);

		return true;
	}

	for (auto &v : m_sub_elements)
		if (v.insert_after(prev, next))
			return true;

	return false;
}

template <typename T>
bool ordered_list<T>::element::insert_before(T prev, T next)
{
	m_count++;

	if (m_count - 1ul == 0ul)
	{
		m_element = prev;
		m_sub_elements.push_back(next);
		m_count++;

		return true;
	}

	if (get_element() == next)
	{
		auto current = *this;
		clear();
		m_element = prev;
		m_sub_elements.push_back(current);

		return true;
	}

	for (auto &v : m_sub_elements)
		if (v.insert_before(prev, next))
			return true;

	return false;
}

template <typename T>
const std::vector<typename ordered_list<T>::element> ordered_list<T>::element::get_sub_elements() const
{
	return m_sub_elements;
}

template <typename T>
void ordered_list<T>::element::clear()
{
	for (auto &v : m_sub_elements)
		v.clear();

	m_sub_elements.clear();
}

template <typename T>
template <typename TType>
ordered_list<T>::element::element(TType value)
	: m_count(1ul)
	, m_element(value)
{
}

template <typename T>
void ordered_list<T>::clear()
{
	m_list.clear();
}

template <typename T>
void ordered_list<T>::order()
{
	for (auto it = m_disconnected.begin(); it != m_disconnected.end();)
	{
		if (!m_list.insert_after(it->first, it->second))
			if (!m_list.insert_before(it->first, it->second))
			{
				++it;
				continue;
			}

		m_disconnected.erase(it);
		it = m_disconnected.begin();
	}
}

template <typename T>
bool ordered_list<T>::is_valid() const
{
	return m_disconnected.empty();
}

template <typename T>
void ordered_list<T>::insert_after(T prev, T next)
{
	if (!m_list.insert_after(prev, next))
		m_disconnected.push_back(std::make_pair(prev, next));
}

template <typename T>
void ordered_list<T>::insert_before(T prev, T next)
{
	if (!m_list.insert_before(prev, next))
		m_disconnected.push_back(std::make_pair(prev, next));
}

template <typename T>
std::uint64_t ordered_list<T>::get_count()
{
	return m_list.get_count();
}

template <typename T>
typename const ordered_list<T>::element& ordered_list<T>::get_head()
{
	return m_list;
}