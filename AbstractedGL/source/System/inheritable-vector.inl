
template <typename T>
CInheritableVector<T>::CInheritableVector(std::uint64_t count)
	: vector_(std::vector<value_type>(count))
{
}

template <typename T>
CInheritableVector<T>::~CInheritableVector()
{
	clear();
}

template <typename T>
typename CInheritableVector<T>::reference CInheritableVector<T>::at(std::uint64_t index)
{
	return vector_.at(index);
}

template <typename T>
typename CInheritableVector<T>::const_reference CInheritableVector<T>::at(std::uint64_t index) const
{
	return vector_.at(index);
}

template <typename T>
typename CInheritableVector<T>::reference CInheritableVector<T>::operator[](std::uint64_t index)
{
	return vector_[index];
}

template <typename T>
typename CInheritableVector<T>::const_reference CInheritableVector<T>::operator[](std::uint64_t index) const
{
	return vector_[index];
}

template <typename T>
typename CInheritableVector<T>::reference CInheritableVector<T>::front()
{
	return vector_.front();
}

template <typename T>
typename CInheritableVector<T>::const_reference CInheritableVector<T>::front() const
{
	return vector_.front();
}

template <typename T>
typename CInheritableVector<T>::reference CInheritableVector<T>::back()
{
	return vector_.back();
}

template <typename T>
typename CInheritableVector<T>::const_reference CInheritableVector<T>::back() const
{
	return vector_.back();
}

template <typename T>
typename CInheritableVector<T>::const_pointer CInheritableVector<T>::data() const
{
	return vector_.data();
}

template <typename T>
typename CInheritableVector<T>::iterator CInheritableVector<T>::begin() const
{
	return vector_.begin();
}

template <typename T>
typename CInheritableVector<T>::iterator CInheritableVector<T>::end() const
{
	return vector_.end();
}

template <typename T>
typename CInheritableVector<T>::const_iterator CInheritableVector<T>::cbegin() const
{
	return vector_.cbegin();
}

template <typename T>
typename CInheritableVector<T>::const_iterator CInheritableVector<T>::cend() const
{
	return vector_.cend();
}

template <typename T>
bool CInheritableVector<T>::empty() const
{
	return vector_.empty();
}

template <typename T>
std::uint64_t CInheritableVector<T>::count() const
{
	return vector_.size();
}

template <typename T>
void CInheritableVector<T>::reserve(std::uint64_t count)
{
	vector_.reserve(count);
}

template <typename T>
std::uint64_t CInheritableVector<T>::capacity() const
{
	return vector_.capacity();
}

template <typename T>
void CInheritableVector<T>::clear()
{
	vector_.clear();
}

template <typename T>
template<class InputIt>
typename CInheritableVector<T>::iterator CInheritableVector<T>::insert(const_iterator position, InputIt first, InputIt last)
{
	vector_.insert(position, first, last);
}

template <typename T>
typename CInheritableVector<T>::iterator CInheritableVector<T>::insert(const_iterator position, std::uint64_t count, const T& value)
{
	vector_.insert(position, count, value);
}

template <typename T>
typename CInheritableVector<T>::iterator CInheritableVector<T>::insert(const_iterator position, T&& value)
{
	vector_.insert(position, value);
}


template <typename T>
void CInheritableVector<T>::erase(iterator position)
{
	vector_.erase(position);
}

template <typename T>
void CInheritableVector<T>::erase(const_iterator position)
{
	vector_.erase(position);
}

template <typename T>
void CInheritableVector<T>::erase(const_iterator first, const_iterator last)
{
	vector_.erase(first, last);
}

template <typename T>
void CInheritableVector<T>::erase(iterator first, iterator last)
{
	vector_.erase(first, last);
}

template <typename T>
void CInheritableVector<T>::resize(std::uint64_t count)
{
	vector_.resize(count);
}

template <typename T>
void CInheritableVector<T>::push_back(T &&element)
{
	vector_.push_back(std::forward<T>(element));
}

template <typename T>
void CInheritableVector<T>::push_back(const T &element)
{
	vector_.push_back(element);
}