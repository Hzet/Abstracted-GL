
// iterator

template <typename T>
bool operator==(render_buffer::iterator<T> const& lhs, render_buffer::iterator<T> const& rhs)
{
	return lhs.m_index == rhs.m_index;
}

template <typename T>
bool operator!=(render_buffer::iterator<T> const& lhs, render_buffer::iterator<T> const& rhs)
{
	return lhs.m_index != rhs.m_index;
}

template <typename T>
bool operator>(render_buffer::iterator<T> const& lhs, render_buffer::iterator<T> const& rhs)
{
	return lhs.m_index > rhs.m_index;
}

template <typename T>
bool operator>=(render_buffer::iterator<T> const& lhs, render_buffer::iterator<T> const& rhs)
{
	return lhs.m_index >= rhs.m_index;
}

template <typename T>
bool operator<=(render_buffer::iterator<T> const& lhs, render_buffer::iterator<T> const& rhs)
{
	return lhs.m_index <= rhs.m_index;
}

template <typename T>
bool operator<(render_buffer::iterator<T> const& lhs, render_buffer::iterator<T> const& rhs)
{
	return lhs.m_index < rhs.m_index;
}

template <typename T>
render_buffer::iterator<T> operator+(int lhs, render_buffer::iterator<T> const& rhs)
{
	auto result = rhs;
	return result += lhs;
}

template <typename T>
render_buffer::iterator<T> operator+(render_buffer::iterator<T> const& lhs, int rhs)
{
	auto result = lhs;
	return result += rhs;
}

template <typename T>
render_buffer::iterator<T> operator-(int lhs, render_buffer::iterator<T> const& rhs)
{
	auto result = rhs;
	return result -= lhs;
}

template <typename T>
render_buffer::iterator<T> operator-(render_buffer::iterator<T> const& lhs, int rhs)
{
	auto result = lhs;
	return result -= rhs;
}

template <typename T>
render_buffer::iterator<T>::iterator()
	: iterator{ nullptr, 0, 0, 0 }
{
}

template <typename T>
render_buffer::iterator<T>::iterator(std::byte* const buffer, std::uint64_t index, std::uint64_t offset, std::uint64_t stride)
	: m_buffer{ buffer }
	, m_index{ index }
	, m_offset{ offset }
	, m_stride{ stride }
{
}

template <typename T>
render_buffer::iterator<T>::~iterator()
{
	m_buffer = nullptr;
}

template <typename T>
render_buffer::iterator<T>& render_buffer::iterator<T>::operator++()
{
	++m_index;
	return *this;
}

template <typename T>
render_buffer::iterator<T> render_buffer::iterator<T>::operator++(int) const
{
	auto result = iterator{ *this };
	result.m_index++;

	return result;
}

template <typename T>
render_buffer::iterator<T>& render_buffer::iterator<T>::operator+=(int n)
{
	m_index += n;
	return *this;
}


template <typename T>
render_buffer::iterator<T>& render_buffer::iterator<T>::operator--()
{
	--m_index;
	return *this;
}

template <typename T>
render_buffer::iterator<T> render_buffer::iterator<T>::operator--(int) const
{
	auto result = iterator{ *this };
	result.m_index--;

	return result;
}

template <typename T>
render_buffer::iterator<T>& render_buffer::iterator<T>::operator-=(int n)
{
	m_index -= n;
	return *this;
}

template <typename T>
typename T::Type& render_buffer::iterator<T>::operator*()
{
	return *reinterpret_cast<typename T::Type*>(m_buffer + m_index * m_stride + m_offset);
}

template <typename T>
typename T::Type* const render_buffer::iterator<T>::operator->()
{
	return reinterpret_cast<typename T::Type*>(m_buffer + m_index * m_stride + m_offset);
}

// const_iterator

template <typename T>
render_buffer::const_iterator<T> operator+(int lhs, render_buffer::const_iterator<T> const& rhs)
{
	auto result = rhs;
	return result += lhs;
}

template <typename T>
render_buffer::const_iterator<T> operator+(render_buffer::const_iterator<T> const& lhs, int rhs)
{
	auto result = lhs;
	return result += rhs;
}

template <typename T>
render_buffer::const_iterator<T> operator-(int lhs, render_buffer::const_iterator<T> const& rhs)
{
	auto result = rhs;
	return result -= lhs;
}

template <typename T>
render_buffer::const_iterator<T> operator-(render_buffer::const_iterator<T> const& lhs, int rhs)
{
	auto result = lhs;
	return result -= rhs;
}

template <typename T>
bool operator==(render_buffer::const_iterator<T> const& lhs, render_buffer::const_iterator<T> const& rhs)
{
	return lhs.m_index == rhs.m_index;
}

template <typename T>
bool operator!=(render_buffer::const_iterator<T> const& lhs, render_buffer::const_iterator<T> const& rhs)
{
	return lhs.m_index != rhs.m_index;
}

template <typename T>
bool operator>(render_buffer::const_iterator<T> const& lhs, render_buffer::const_iterator<T> const& rhs)
{
	return lhs.m_index > rhs.m_index;
}

template <typename T>
bool operator>=(render_buffer::const_iterator<T> const& lhs, render_buffer::const_iterator<T> const& rhs)
{
	return lhs.m_index >= rhs.m_index;
}

template <typename T>
bool operator<=(render_buffer::const_iterator<T> const& lhs, render_buffer::const_iterator<T> const& rhs)
{
	return lhs.m_index <= rhs.m_index;
}

template <typename T>
bool operator<(render_buffer::const_iterator<T> const& lhs, render_buffer::const_iterator<T> const& rhs)
{
	return lhs.m_index < rhs.m_index;
}

template <typename T>
render_buffer::const_iterator<T>::const_iterator()
	: const_iterator{ nullptr, 0, 0, 0 }
{
}

template <typename T>
render_buffer::const_iterator<T>::const_iterator(std::byte* const buffer, std::uint64_t index, std::uint64_t offset, std::uint64_t stride)
	: m_buffer{ buffer }
	, m_index{ index }
	, m_offset{ offset }
	, m_stride{ stride }
{
}

template <typename T>
render_buffer::const_iterator<T>::~const_iterator()
{
	m_buffer = nullptr;
}

template <typename T>
render_buffer::const_iterator<T>& render_buffer::const_iterator<T>::operator++()
{
	++m_index;
	return *this;
}

template <typename T>
render_buffer::const_iterator<T> render_buffer::const_iterator<T>::operator++(int) const
{
	auto result = iterator{ *this };
	result.m_index++;

	return result;
}

template <typename T>
render_buffer::const_iterator<T>& render_buffer::const_iterator<T>::operator+=(int n)
{
	m_index += n;
	return *this;
}


template <typename T>
render_buffer::const_iterator<T>& render_buffer::const_iterator<T>::operator--()
{
	--m_index;
	return *this;
}

template <typename T>
render_buffer::const_iterator<T> render_buffer::const_iterator<T>::operator--(int) const
{
	auto result = iterator{ *this };
	result.m_index--;

	return result;
}

template <typename T>
render_buffer::const_iterator<T>& render_buffer::const_iterator<T>::operator-=(int n)
{
	m_index -= n;
	return *this;
}

template <typename T>
typename T::Type const& render_buffer::const_iterator<T>::operator*()
{
	return *reinterpret_cast<typename T::Type*>(m_buffer + m_index * m_stride + m_offset);
}

template <typename T>
typename T::Type const* const render_buffer::const_iterator<T>::operator->()
{
	return reinterpret_cast<typename T::Type*>(m_buffer + m_index * m_stride + m_offset);
}

// render_buffer

template <typename T>
render_buffer::array_info const& render_buffer::add_vertex_type()
{
	auto const id_render = render_type_uid::get_id<T>();

	//AGL_CORE_ASSERT((!std::is_same_v<T, position_2d> && !has_vertex_type<position_3d>()), "\"position_3d\" vertices already set - cannot add \"position_2d\" vertices");
	//AGL_CORE_ASSERT((!std::is_same_v<T, position_3d> && !has_vertex_type<position_2d>()), "\"position_2d\" vertices already set - cannot add \"position_3d\" vertices");

	if (has_vertex_type<T>())
		return get_array_info<T>();

	m_require_update = true;

	auto const old_stride_size = get_stride_size();

	m_array_info.push_back(array_info{ id_render, m_vlayout.get_count(), 0, sizeof(T::Type) });
	m_vlayout.add_element<T::Type>();

	m_vertices.resize(m_vcount * get_stride_size());

	if (get_vertex_count() > 0 && get_stride_count() > 1)
	{
		// reorganize the buffer to match modified stride layout
		for (int i = get_vertex_count() - 1; i >= 0; --i)
			for (int j = get_stride_count() - 2; j >= 0; --j) // one less for the one pushed to the end (line 15 of this file)
				for (int k = m_vlayout[j].size - 1; k >= 0; --k)
					m_vertices[i * get_stride_size() + m_vlayout[j].offset + k] = m_vertices[i * old_stride_size + k];
	}

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
	
	auto vertex_index = std::uint64_t{};
	if (ainfo.array_element_count < get_vertex_count())
		vertex_index = ainfo.array_element_count;
	else
	{
		vertex_index = m_vcount - 1;
		resize(get_vertex_count() + 1);
	}
	
	auto insertion_offset = get_offset<T>(vertex_index);
	auto const* const buffer = reinterpret_cast<std::byte*>(&vertex);

	for (auto i = 0; i < sizeof(T::Type); ++i)
		m_vertices[insertion_offset + i] = *(buffer + i);
}

template <typename T, typename TForwardIterator>
void render_buffer::push_vertices(TForwardIterator begin, TForwardIterator end)
{
	auto const data_count = std::distance(begin, end);

	auto ainfo = add_vertex_type<T>();

	auto vertex_index = std::uint64_t{};
	if (ainfo.array_element_count < get_vertex_count())
		vertex_index = ainfo.array_element_count;
	else
	{
		vertex_index = get_vertex_count();
		resize(get_vertex_count() + data_count);
	}

	for (auto it = begin; it != end; ++it, ++vertex_index)
	{
		auto insertion_offset = get_offset<T>(vertex_index);
		auto const* const buffer = reinterpret_cast<std::byte const* const>(&(*it));

		for (auto i = 0; i < sizeof(T::Type); ++i)
			m_vertices[insertion_offset + i] = *(buffer + i);
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

template <typename T>
render_buffer::iterator<T> render_buffer::begin()
{
	auto const ainfo = get_array_info<T>();

	return iterator<T>{ m_vertices.data(), 0, m_vlayout[ainfo.array_index].offset, m_vlayout.get_size() };
}

template <typename T>
render_buffer::iterator<T> render_buffer::end()
{
	auto const ainfo = get_array_info<T>();

	return iterator<T>{ m_vertices.data(), get_vertex_count(), m_vlayout[ainfo.array_index].offset, m_vlayout.get_size() };
}

template <typename T>
render_buffer::const_iterator<T> render_buffer::cbegin() const
{
	auto const ainfo = get_array_info<T>();

	return iterator<T>{ m_vertices.data(), 0, m_vlayout[ainfo.array_index].offset, m_vlayout.get_size() };
}

template <typename T>
render_buffer::const_iterator<T> render_buffer::cend() const
{
	auto const ainfo = get_array_info<T>();

	return const_iterator<T>{ m_vertices.data(), get_vertex_count(), m_vlayout[ainfo.array_index].offset, m_vlayout.get_size() };
}