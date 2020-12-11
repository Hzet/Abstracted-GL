template <typename T> void CVertexLayout::addElement()
{
	static_assert(false, "No specialization found for type T");
}

template <> void CVertexLayout::addElement<std::uint8_t>()
{
	elements_.push_back({ GL_UNSIGNED_BYTE, GetTypeSize(GL_UNSIGNED_BYTE), 1u, true });
	stride_ += GetTypeSize(GL_UNSIGNED_BYTE);
}

template <> void CVertexLayout::addElement<std::uint32_t>()
{
	elements_.push_back({ GL_UNSIGNED_INT, GetTypeSize(GL_UNSIGNED_INT), 1u, true });
	stride_ += GetTypeSize(GL_UNSIGNED_INT);
}

template <> void CVertexLayout::addElement<float>() 
{
	elements_.push_back({ GL_FLOAT, GetTypeSize(GL_FLOAT), 1u, true });
	stride_ += GetTypeSize(GL_FLOAT);
}

template <> void CVertexLayout::addElement<glm::vec2>()
{
	elements_.push_back({ GL_FLOAT, GetTypeSize(GL_FLOAT) * 2u, 2u, true });
	stride_ += GetTypeSize(GL_FLOAT) * 2u;
}

template <> void CVertexLayout::addElement<glm::vec3>()
{
	elements_.push_back({ GL_FLOAT, GetTypeSize(GL_FLOAT) * 3u, 3u, true });
	stride_ += GetTypeSize(GL_FLOAT) * 3u;
}

template <> void CVertexLayout::addElement<glm::vec4>()
{
	elements_.push_back({ GL_FLOAT, GetTypeSize(GL_FLOAT) * 4u, 4u, true });
	stride_ += GetTypeSize(GL_FLOAT) * 4u;
}