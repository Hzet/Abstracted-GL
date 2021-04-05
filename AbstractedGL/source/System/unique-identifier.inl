template <typename T>
TUID<T>::TUID()
	: uid_(Register())
{
}

template <typename T>
TUID<T>::TUID(InvalidValue)
	: uid_(0u)
{
}

template <typename T>
TUID<T>::TUID(std::uint64_t uid)
	: uid_(uid)
{
}

template <typename T>
TUID<T>::~TUID()
{
	Unregister(*this);
}

template <typename T>
TUID<T>::TUID(TUID &&other)
	: uid_(other.uid_)
{
	other.uid_ = 0u;
}

template <typename T>
TUID<T>::TUID(const TUID &other)
	: uid_(other.uid_)
{
	RegisteredIdentifiers()[uid_]++;
}

template <typename T>
TUID<T>& TUID<T>::operator=(TUID &&other)
{
	std::swap(uid_, other.uid_);

	return *this;
}

template <typename T>
TUID<T>& TUID<T>::operator=(const TUID &other)
{
	uid_ = other.uid_; 
	RegisteredIdentifiers()[uid_]++;

	return *this;
}

template <typename T>
TUID<T>::operator std::uint64_t() const
{
	return uid_;
}

template <typename T>
std::uint64_t TUID<T>::Register()
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
void TUID<T>::Unregister(TUID<T> &uid)
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
std::map<std::uint64_t, std::uint64_t>& TUID<T>::RegisteredIdentifiers()
{
	static std::map<std::uint64_t, std::uint64_t> Identifiers;

	return Identifiers;
}
