template <class... Args>
TTupleBuffer<Args...>::TTupleBuffer() noexcept
{}
/*

template <class... Args>
CTupleBuffer<Args...>::CTupleBuffer(Args&&... elems)
{
	push_back(std::forward<Args>(elems)...);
}
*/

template <class... Args>
TTupleBuffer<Args...>::~TTupleBuffer()
{
	clear();
}

template <class... Args>
void TTupleBuffer<Args...>::push_back(Args&&... elems)
{
	data_.resize((getCount() + 1u) * getStrideSize());

	this->ConstructValueAll(getStoragePointer<0>(getCount() - 1u), std::forward<Args>(elems)...);
}

template <class... Args>
void TTupleBuffer<Args...>::clear()
{
	const std::size_t size = data_.size();
	std::byte * const data = data_.data();

	for (std::size_t i = 0u; i < size; i += getStrideSize())
		this->DestructAll(data + i);

	data_.clear();
}

template <class... Args>
void TTupleBuffer<Args...>::resize(std::size_t count)
{
	if (count == getCount())
		return;
	else if (count == 0u)
	{
		clear();
		return;
	}

	const std::size_t newSize = count * getStrideSize();
	const std::size_t oldSize = data_.size();

	if (count < getCount())
	{
		std::byte * const data = data_.data();
		for (std::size_t i = newSize; i < oldSize; i += getStrideSize())
			this->DestructAll(data + i);

		data_.resize(newSize);
	}
	else if (count > getCount())
	{
		data_.resize(newSize);

		std::byte * const data = data_.data();
		for (std::size_t i = oldSize; i < newSize; i += getStrideSize())
			this->ConstructAll(data + i);
	}
}


template <class... Args>
std::size_t TTupleBuffer<Args...>::getSize() const
{
	return data_.size();
}

template <class... Args>
std::size_t TTupleBuffer<Args...>::getCount() const
{
	return getSize() / getStrideSize();
}

template <class... Args>
std::size_t TTupleBuffer<Args...>::getStrideSize() const
{
	return this->StrideSize_;
}

template <class... Args>
std::size_t TTupleBuffer<Args...>::getStrideCount() const
{
	return this->StrideCount_;
}

template <class... Args>
template <std::size_t I>
auto& TTupleBuffer<Args...>::get(std::size_t index)
{
	this->CheckRange<I>();

	return *getPointer<I>(index);
}

template <class... Args>
template <std::size_t I>
const auto& TTupleBuffer<Args...>::get(std::size_t index) const
{
	this->CheckRange<I>();

	return *getPointer<I>(index);
}

template <class... Args>
std::byte const * const TTupleBuffer<Args...>::getData() const
{
	return data_.data();
}

template <class... Args>
template <std::size_t I>
auto * const TTupleBuffer<Args...>::getPointer(std::size_t index)
{
	return this->GetPointer<I>(data_.data() + getStrideSize() * index);
}

template <class... Args>
template <std::size_t I>
auto const * const TTupleBuffer<Args...>::getPointer(std::size_t index) const
{
	return this->GetPointer<I>(data_.data() + getStrideSize() * index);
}

template <class... Args>
template <std::size_t I>
std::byte * const TTupleBuffer<Args...>::getStoragePointer(std::size_t index)
{
	return data_.data() + this->GetElementOffset<I>() + getStrideSize() * index;
}

template <class... Args>
template <std::size_t I>
std::byte const * const TTupleBuffer<Args...>::getStoragePointer(std::size_t index) const
{
	return data_.data() + this->GetElementOffset<I>() + getStrideSize() * index;
}