#include "vertex-layout.hpp"

#include "../System/gl-core.hpp"

namespace agl
{
	std::uint64_t CVertexLayout::GetTypeSize(const std::uint64_t type)
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

	std::uint64_t CVertexLayout::getStride() const
	{
		return stride_;
	}

	std::uint64_t CVertexLayout::getCount() const
	{
		return elements_.size();
	}

	const agl::CVertexLayout::SElement& CVertexLayout::operator[](const std::uint64_t index) const
	{
		return elements_[index];
	}

}