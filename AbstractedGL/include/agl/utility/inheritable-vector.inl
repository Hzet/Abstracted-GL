
template <typename T>
vector_base<T>::vector_base(std::uint64_t count)
	: m_vector(std::vector<value_type>(count))
{
}

template <typename T>
vector_base<T>::~vector_base()
{
	clear();
}

template <typename T>
typename vector_base<T>::reference vector_base<T>::at(std::uint64_t index)
{
	return m_vector.at(index);
}

template <typename T>
typename vector_base<T>::const_reference vector_base<T>::at(std::uint64_t index) const
{
	return m_vector.at(index);
}

template <typename T>
typename vector_base<T>::reference vector_base<T>::operator[](std::uint64_t index)
{
	return m_vector[index];
}

template <typename T>
typename vector_base<T>::const_reference vector_base<T>::operator[](std::uint64_t index) const
{
	return m_vector[index];
}

template <typename T>
typename vector_base<T>::reference vector_base<T>::front()
{
	return m_vector.front();
}

template <typename T>
typename vector_base<T>::const_reference vector_base<T>::front() const
{
	return m_vector.front();
}

template <typename T>
typename vector_base<T>::reference vector_base<T>::back()
{
	return m_vector.back();
}

template <typename T>
typename vector_base<T>::const_reference vector_base<T>::back() const
{
	return m_vector.back();
}

template <typename T>
typename vector_base<T>::const_pointer vector_base<T>::data() const
{
	return m_vector.data();
}

template <typename T>
typename std::vector<T>::iterator vector_base<T>::begin()
{
	return m_vector.begin();
}

template <typename T>
typename vector_base<T>::iterator vector_base<T>::end()
{
	return m_vector.end();
}

template <typename T>
typename vector_base<T>::const_iterator vector_base<T>::begin() const
{
	return m_vector.begin();
}

template <typename T>
typename vector_base<T>::const_iterator vector_base<T>::end() const
{
	return m_vector.end();
}

template <typename T>
bool vector_base<T>::empty() const
{
	return m_vector.empty();
}

template <typename T>
std::uint64_t vector_base<T>::count() const
{
	return m_vector.size();
}

template <typename T>
void vector_base<T>::reserve(std::uint64_t count)
{
	m_vector.reserve(count);
}

template <typename T>
std::uint64_t vector_base<T>::capacity() const
{
	return m_vector.capacity();
}

template <typename T>
void vector_base<T>::clear()
{
	this->on_update();

	m_vector.clear();
}

template <typename T>
template<class InputIt>
typename vector_base<T>::iterator vector_base<T>::insert(const_iterator position, InputIt first, InputIt last)
{
	m_vector.insert(position, first, last);

	this->on_update();
}

template <typename T>
typename vector_base<T>::iterator vector_base<T>::insert(const_iterator position, std::uint64_t count, const T& value)
{
	m_vector.insert(position, count, value);

	this->on_update();
}

template <typename T>
typename vector_base<T>::iterator vector_base<T>::insert(const_iterator position, T&& value)
{
	m_vector.insert(position, value);

	this->on_update();
}


template <typename T>
void vector_base<T>::erase(iterator position)
{
	m_vector.erase(position);

	this->on_update();
}

template <typename T>
void vector_base<T>::erase(const_iterator position)
{
	m_vector.erase(position);

	this->on_update();
}

template <typename T>
void vector_base<T>::erase(const_iterator first, const_iterator last)
{
	m_vector.erase(first, last);

	this->on_update();
}

template <typename T>
void vector_base<T>::erase(iterator first, iterator last)
{
	m_vector.erase(first, last);

	this->on_update();
}

template <typename T>
void vector_base<T>::resize(std::uint64_t count)
{
	m_vector.resize(count);

	this->on_update();
}

template <typename T>
void vector_base<T>::push_back(T &&element)
{
	m_vector.push_back(std::forward<T>(element));

	this->on_update();
}

template <typename T>
void vector_base<T>::push_back(const T &element)
{
	m_vector.push_back(element);

	this->on_update();
}