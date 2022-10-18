template <typename T>
void render_buffer::add_vertices(const std::vector<T> &data)
{
	add_vertices(data.data());
}

template <typename T>
void render_buffer::add_vertices(const T * const data)
{
	m_require_update = true;

	const auto renderTypeUID = TRenderTypeUID<T>::value();
	auto found = m_index_map.find(renderTypeUID);

	if (found != m_index_map.end())
	{
		for (std::uint64_t i = 0ul; i < get_vertex_count(); i++)
			get<T>(i) = *(data + i);

		return;
	}

	found = m_index_map.insert(renderTypeUID, m_vlayout.get_count());
	m_vlayout.add_element<T::Type>();
	m_vertices.reserve(m_vertices.size() + (m_vcount * sizeof(T::Type)));

	std::uint64_t offset = get_offset<T>(0ul);
	for (std::uint64_t i = 0ul; i < get_vertex_count(); i++)
	{
		const auto * const flat = reinterpret_cast<const std::byte *const>(data + i);

		m_vertices.insert(m_vertices.begin() + offset, flat, flat + sizeof(T::Type));

		offset += get_stride_size();
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
	const auto typeIndex = m_index_map.find(TRenderTypeUID<T>::value())->second;
	return m_vlayout[typeIndex].offset + (m_vlayout.get_size() * index);
}
