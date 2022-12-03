template <typename T>
render_buffer::array_info const& render_buffer::add_vertex_type()
{
	auto const id_render = render_type_uid::get_id<T>();

	if (has_vertex_type<T>())
		return get_array_info<T>();

	m_array_indexes.push_back(array_info{ id_render, m_vlayout.get_count(), 0 });
	m_vlayout.add_element<T::Type>();

	m_require_update = true;

	return m_array_indexes.back();
}

template <typename T>
render_buffer::array_info const& render_buffer::get_array_info() const
{
	auto const id_render = render_type_uid::get_id<T>();

	for (auto const& info : m_array_indexes)
		if (info.id_render == id_render)
			return info;

	AGL_CORE_ASSERT(false, "Index out of bounds! Type {} not present", render_type_uid::get_name(id_render));
}

template <typename T>
bool render_buffer::has_vertex_type() const
{
	auto const id_render = render_type_uid::get_id<T>();

	for (auto const& info : m_array_indexes)
		if (info.id_render == id_render)
			return true;

	return false;
}

template <typename TForwardIterator>
void render_buffer::push_indices(TForwardIterator begin, TForwardIterator end)
{
	m_require_update = true;

	auto const count = std::distance(begin, end);

	m_indices.clear();
	m_indices.reserve(count);

	for (auto it = begin; it != end; ++it)
		m_indices.push_back(*it);
}

template <typename T>
void render_buffer::push_vertex(T vertex)
{
	auto ainfo = add_vertex_type<T>();

	if (ainfo.array_size >= get_vertex_count())
		reserve(get_vertex_count() + 1);
	else
		reserve(get_vertex_count());

	auto const* const flat_begin = *reinterpret_cast<std::byte const * const>(&(*vertex));
	auto const* const flat_end = flat_begin + sizeof(T::Type);
	auto const insert = m_vertices.cbegin() + get_offset<T>(get_vertex_count() - 1);
	
	m_vertices.insert(insert, flat_begin, flat_end);
}

template <typename T, typename TForwardIterator>
void render_buffer::push_vertices(TForwardIterator begin, TForwardIterator end)
{
	auto const data_count = std::distance(begin, end);

	if (data_count == 0)
		return;

	auto ainfo = add_vertex_type<T>();

	if (ainfo.array_size+ data_count > get_vertex_count())
		reserve(get_vertex_count() - ainfo.array_size + data_count);
	else
		reserve(get_vertex_count());

	auto i = ainfo.array_size == 0 ? 0 : ainfo.array_size - 1;
	for (auto it = begin; it != end; ++it, ++i)
	{
		auto const* const flat_begin = reinterpret_cast<std::byte const * const>(&(*it));
		auto const* const flat_end = flat_begin + sizeof(T::Type);
		auto const insert = m_vertices.cbegin() + get_offset<T>(i);

		m_vertices.insert(insert, flat_begin, flat_end);
	}
}

template <typename T>
T& render_buffer::get(std::uint64_t index)
{
	m_require_update = true;

	return *reinterpret_cast<T*>(m_vertices.data() + get_offset<T>(index));
}

template <typename T>
const T& render_buffer::get(std::uint64_t index) const
{
	return *reinterpret_cast<T const*>(m_vertices.data() + get_offset<T>(index));
}

template <typename T>
std::uint64_t render_buffer::get_offset(std::uint64_t index) const
{
	const auto data = get_array_info<T>();
	return m_vlayout[data.array_index].offset + (m_vlayout.get_size() * index);
}
