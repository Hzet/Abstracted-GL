template <typename T>
render_buffer::array_info const& render_buffer::add_vertex_type()
{
	auto const id_render = render_type_uid::get_id<T>();

	if (has_vertex_type<T>())
		return get_array_info<T>();

	m_array_info.push_back(array_info{ id_render, m_vlayout.get_count(), sizeof(T::Type) });
	m_destructors.push_back(std::unique_ptr<render_type_destructor_base>(new render_type_destructor<T::Type>()));
	m_vlayout.add_element<T::Type>();

	m_require_update = true;

	return m_array_info.back();
}

template <typename T>
render_buffer::array_info const& render_buffer::get_array_info() const
{
	auto const id_render = render_type_uid::get_id<T>();

	for (auto const& info : m_array_info)
		if (info.id_render == id_render)
			return info;

	AGL_CORE_ASSERT(false, "Index out of bounds! Type {} not present", render_type_uid::get_name(id_render));
}

template <typename T>
bool render_buffer::has_vertex_type() const
{
	auto const id_render = render_type_uid::get_id<T>();

	for (auto const& info : m_array_info)
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
	
	resize(get_vertex_count() + 1);
	
	auto * const insertion_offset = m_vertices.data() + get_offset<T>(m_vcount - 1);

	new (insertion_offset) typename T::Type(vertex);
}

template <typename T, typename TForwardIterator>
void render_buffer::push_vertices(TForwardIterator begin, TForwardIterator end)
{
	auto const data_count = std::distance(begin, end);

	auto ainfo = add_vertex_type<T>();

	resize(get_vertex_count() + data_count);

	auto i = get_vertex_count() - data_count;
	for (auto it = begin; it != end; ++it, ++i)
	{
		auto * const insertion_offset = m_vertices.data() + get_offset<T>(i);

		new (insertion_offset) typename T::Type(*it);
	}
}

template <typename T>
auto& render_buffer::get(std::uint64_t index)
{
	m_require_update = true;

	return *reinterpret_cast<typename T::Type*>(m_vertices.data() + get_offset<T>(index));
}

template <typename T>
auto const& render_buffer::get(std::uint64_t index) const
{
	return *reinterpret_cast<typename T::Type const*>(m_vertices.data() + get_offset<T>(index));
}

template <typename T>
std::uint64_t render_buffer::get_offset(std::uint64_t index) const
{
	const auto data = get_array_info<T>();
	return m_vlayout[data.array_index].offset + (m_vlayout.get_size() * index);
}
