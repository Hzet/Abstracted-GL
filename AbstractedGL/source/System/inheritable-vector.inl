
template <typename T>
IInheritableVector<T>::IInheritableVector(std::uint64_t count)
	: vector_(std::vector<value_type>(count))
{
}

template <typename T>
IInheritableVector<T>::~IInheritableVector()
{
	clear();
}

template <typename T>
typename IInheritableVector<T>::reference IInheritableVector<T>::at(std::uint64_t index)
{
	return vector_.at(index);
}

template <typename T>
typename IInheritableVector<T>::const_reference IInheritableVector<T>::at(std::uint64_t index) const
{
	return vector_.at(index);
}

template <typename T>
typename IInheritableVector<T>::reference IInheritableVector<T>::operator[](std::uint64_t index)
{
	return vector_[index];
}

template <typename T>
typename IInheritableVector<T>::const_reference IInheritableVector<T>::operator[](std::uint64_t index) const
{
	return vector_[index];
}

template <typename T>
typename IInheritableVector<T>::reference IInheritableVector<T>::front()
{
	return vector_.front();
}

template <typename T>
typename IInheritableVector<T>::const_reference IInheritableVector<T>::front() const
{
	return vector_.front();
}

template <typename T>
typename IInheritableVector<T>::reference IInheritableVector<T>::back()
{
	return vector_.back();
}

template <typename T>
typename IInheritableVector<T>::const_reference IInheritableVector<T>::back() const
{
	return vector_.back();
}

template <typename T>
typename IInheritableVector<T>::const_pointer IInheritableVector<T>::data() const
{
	return vector_.data();
}

template <typename T>
typename std::vector<T>::iterator IInheritableVector<T>::begin()
{
	return vector_.begin();
}

template <typename T>
typename IInheritableVector<T>::iterator IInheritableVector<T>::end()
{
	return vector_.end();
}

template <typename T>
typename IInheritableVector<T>::const_iterator IInheritableVector<T>::cbegin() const
{
	return vector_.cbegin();
}

template <typename T>
typename IInheritableVector<T>::const_iterator IInheritableVector<T>::cend() const
{
	return vector_.cend();
}

template <typename T>
bool IInheritableVector<T>::empty() const
{
	return vector_.empty();
}

template <typename T>
std::uint64_t IInheritableVector<T>::count() const
{
	return vector_.size();
}

template <typename T>
void IInheritableVector<T>::reserve(std::uint64_t count)
{
	vector_.reserve(count);
}

template <typename T>
std::uint64_t IInheritableVector<T>::capacity() const
{
	return vector_.capacity();
}

template <typename T>
void IInheritableVector<T>::clear()
{
	this->onUpdate();

	vector_.clear();
}

template <typename T>
template<class InputIt>
typename IInheritableVector<T>::iterator IInheritableVector<T>::insert(const_iterator position, InputIt first, InputIt last)
{
	vector_.insert(position, first, last);

	this->onUpdate();
}

template <typename T>
typename IInheritableVector<T>::iterator IInheritableVector<T>::insert(const_iterator position, std::uint64_t count, const T& value)
{
	vector_.insert(position, count, value);

	this->onUpdate();
}

template <typename T>
typename IInheritableVector<T>::iterator IInheritableVector<T>::insert(const_iterator position, T&& value)
{
	vector_.insert(position, value);

	this->onUpdate();
}


template <typename T>
void IInheritableVector<T>::erase(iterator position)
{
	vector_.erase(position);

	this->onUpdate();
}

template <typename T>
void IInheritableVector<T>::erase(const_iterator position)
{
	vector_.erase(position);

	this->onUpdate();
}

template <typename T>
void IInheritableVector<T>::erase(const_iterator first, const_iterator last)
{
	vector_.erase(first, last);

	this->onUpdate();
}

template <typename T>
void IInheritableVector<T>::erase(iterator first, iterator last)
{
	vector_.erase(first, last);

	this->onUpdate();
}

template <typename T>
void IInheritableVector<T>::resize(std::uint64_t count)
{
	vector_.resize(count);

	this->onUpdate();
}

template <typename T>
void IInheritableVector<T>::push_back(T &&element)
{
	vector_.push_back(std::forward<T>(element));

	this->onUpdate();
}

template <typename T>
void IInheritableVector<T>::push_back(const T &element)
{
	vector_.push_back(element);

	this->onUpdate();
}