template <typename TName>
template <typename T>
unique_type_id<TName> unique_type_id<TName>::get_id()
{
	static auto result = unique_type_id<TName>{ ++unique_type_id<TName>::incrementor() };

#ifdef AGL_DEBUG
	static auto& names = unique_type_id_debug::get_names_ref();
	static auto names_bool = { names[typeid(TName).name()][result] = typeid(T).name() };
#endif 

	return result;
}

template <typename TName>
std::unordered_map<std::uint64_t, std::string> const& unique_type_id<TName>::get_names()
{
#ifdef AGL_DEBUG
	auto& names = unique_type_id_debug::get_names_ref();
	return names[typeid(TName).name()];
#else
	return "name not available in non debug mode";
#endif
}

template <typename TName>
std::string const& unique_type_id<TName>::get_name(std::uint64_t id)
{
#ifdef AGL_DEBUG
	auto const& names = unique_type_id_debug::get_names();

	return names.at(typeid(TName).name()).at(id);
#else
	return "name not available in non debug mode";
#endif
}

template <typename TName>
std::uint64_t& unique_type_id<TName>::incrementor()
{
	static std::uint64_t Result = 0ul;

	return Result;
}

template <typename TName>
unique_type_id<TName>::unique_type_id()
	: m_id(INVALID)
{
}

template <typename TName>
unique_type_id<TName>::unique_type_id(std::uint64_t uid)
	: m_id(uid)
{
}

template <typename TName>
unique_type_id<TName>::operator std::uint64_t() const
{
	return m_id;
}