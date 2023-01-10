
template <typename T>
template <typename... Args>
signal<T>::signal(Args&&... args)
{
	get() = T{ std::forward<Args>(args)... };
}

template <typename T>
signal<T>::signal(signal &&other)
{
	get() = std::move(other.get());
}

template <typename T>
signal<T>::signal(const signal &other)
{
	get() = other.get();
}

template <typename T>
signal<T>& signal<T>::operator=(signal &&other)
{
	get() = std::move(other.m_data);

	return *this;
}

template <typename T>
signal<T>& signal<T>::operator=(const signal &other)
{
	get() = other.get();

	return *this;
}

template <typename T>
template <typename U> signal<T>& signal<T>::operator=(U &&value)
{
	get() = std::move(value);

	return *this;
}
template <typename T>
template <typename U> signal<T>& signal<T>::operator=(const U &value)
{
	get() = value;

	return *this;
}

template <typename T>
signal<T>::operator T&()
{
	return get();
}

template <typename T>
signal<T>::operator T&() const
{
	return get();
}

template <typename T>
T& signal<T>::get()
{
	return m_data;
}

template <typename T>
const T& signal<T>::get() const
{
	return m_data;
}