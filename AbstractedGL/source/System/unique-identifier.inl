template <typename T>
CUID<T>::CUID()
	: uid_(Register())
{
}

template <typename T>
CUID<T>::CUID(InvalidValue)
	: uid_(0u)
{
}

template <typename T>
CUID<T>::CUID(std::uint64_t uid)
	: uid_(uid)
{
}

template <typename T>
CUID<T>::~CUID()
{
	Unregister(*this);
}

template <typename T>
CUID<T>::CUID(CUID &&other)
	: uid_(other.uid_)
{
	other.uid_ = 0u;
}

template <typename T>
CUID<T>::CUID(const CUID &other)
	: uid_(other.uid_)
{
	RegisteredIdentifiers()[uid_]++;
}

template <typename T>
CUID<T>& CUID<T>::operator=(CUID &&other)
{
	std::swap(uid_, other.uid_);

	return *this;
}

template <typename T>
CUID<T>& CUID<T>::operator=(const CUID &other)
{
	uid_ = other.uid_; 
	RegisteredIdentifiers()[uid_]++;

	return *this;
}

template <typename T>
CUID<T>::operator std::uint64_t() const
{
	return uid_;
}

template <typename T>
std::uint64_t CUID<T>::Register()
{
	std::uint64_t expected = 1u;
	for (const auto &m : RegisteredIdentifiers())
	{
		if (m.first != expected)
			break;

		expected++;
	}

	RegisteredIdentifiers().emplace(expected, 1u);
	return { expected };
}

template <typename T> 
void CUID<T>::Unregister(CUID<T> &uid)
{
	if (uid == 0u)
		return;

	auto found = RegisteredIdentifiers().find(uid);

	if (found != RegisteredIdentifiers().end())
	{
		if (found->second > 1u)
			found->second--;
		else
			RegisteredIdentifiers().erase(found);
		uid.uid_ = 0u;
	}
}

template <typename T>
std::map<std::uint64_t, std::uint64_t>& CUID<T>::RegisteredIdentifiers()
{
	static std::map<std::uint64_t, std::uint64_t> Identifiers;

	return Identifiers;
}
