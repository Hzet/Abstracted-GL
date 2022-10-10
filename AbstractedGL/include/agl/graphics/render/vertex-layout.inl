constexpr std::uint32_t vertex_layout::get_type_size(const std::uint32_t type)
{
	switch (type)
	{
	case GL_FLOAT: return sizeof(float);
	case GL_INT: return sizeof(std::uint32_t);
	case GL_UNSIGNED_INT: return sizeof(std::uint32_t);
	case GL_UNSIGNED_BYTE: return sizeof(std::uint8_t);
	}

	AGL_CORE_ASSERT(false, "Unknown buffer data type!");
	return 0u;
}

template <class T> 
void vertex_layout::add_element()
{
	m_elements.push_back(get_element<T>());
	m_stride += m_elements.back().size;
}

template <class T> 
vertex_layout::element vertex_layout::get_element()
{
	static_assert(false, "No specialization found for type T");
}

template <> 
vertex_layout::element vertex_layout::get_element<std::uint8_t>()
{
	return { GL_UNSIGNED_BYTE, get_type_size(GL_UNSIGNED_BYTE), 1u, get_size(), true };
}

template <> vertex_layout::element vertex_layout::get_element<std::uint32_t>()
{
	return { GL_UNSIGNED_INT, get_type_size(GL_UNSIGNED_INT), 1u, get_size(), true };
}

template <> 
vertex_layout::element vertex_layout::get_element<float>()
{
	return { GL_UNSIGNED_INT, get_type_size(GL_UNSIGNED_INT), 1u, get_size(), true };
}

template <> 
vertex_layout::element vertex_layout::get_element<glm::vec2>()
{
	return { GL_FLOAT, get_type_size(GL_FLOAT) * 2u, 2u, get_size(), true };
}

template <>
vertex_layout::element vertex_layout::get_element<glm::vec3>()
{
	return { GL_FLOAT, get_type_size(GL_FLOAT) * 3u, 3u, get_size(), true };
}

template <> 
vertex_layout::element vertex_layout::get_element<glm::vec4>()
{
	return { GL_FLOAT, get_type_size(GL_FLOAT) * 4u, 4u, get_size(), true };
}
