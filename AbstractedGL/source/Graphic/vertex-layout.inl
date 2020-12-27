constexpr CVertexLayout::SElement::SElement(const std::uint64_t t, const std::uint64_t s, const std::uint32_t c, const bool n)
	: type(t),
	size(s),
	count(c),
	normalized(n)
{
}

constexpr std::uint64_t CVertexLayout::GetTypeSize(const std::uint64_t type)
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

template <class T> void CVertexLayout::addElement()
{
	elements_.push_back(GetElement<T>());
	stride_ += elements_.back().size;
}

template <class T> constexpr CVertexLayout::SElement CVertexLayout::GetElement()
{
	static_assert(false, "No specialization found for type T");
}

template <> constexpr CVertexLayout::SElement CVertexLayout::GetElement<std::uint8_t>()
{
	return { GL_UNSIGNED_BYTE, GetTypeSize(GL_UNSIGNED_BYTE), 1u, true };
}

template <> constexpr CVertexLayout::SElement CVertexLayout::GetElement<std::uint32_t>()
{
	return { GL_UNSIGNED_INT, GetTypeSize(GL_UNSIGNED_INT), 1u, true };
}

template <> constexpr CVertexLayout::SElement CVertexLayout::GetElement<float>()
{
	return { GL_UNSIGNED_INT, GetTypeSize(GL_UNSIGNED_INT), 1u, true };
}

template <> constexpr CVertexLayout::SElement CVertexLayout::GetElement<glm::vec2>()
{
	return { GL_FLOAT, GetTypeSize(GL_FLOAT) * 2u, 2u, true };
}

template <> constexpr CVertexLayout::SElement CVertexLayout::GetElement<glm::vec3>()
{
	return { GL_FLOAT, GetTypeSize(GL_FLOAT) * 3u, 3u, true };
}

template <> constexpr CVertexLayout::SElement CVertexLayout::GetElement<glm::vec4>()
{
	return { GL_FLOAT, GetTypeSize(GL_FLOAT) * 4u, 4u, true };
}
