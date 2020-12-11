#include "vertex-buffer.hpp"
#include "../System/gl-core.hpp"

namespace agl
{
	CVertexBuffer::CVertexBuffer()
		: size_(0u),
		count_(0u)
	{
	}

	CVertexBuffer::~CVertexBuffer()
	{
		if (!isMoveConstructing())
			destroy();
	}

	void CVertexBuffer::bind() const
{
		AGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferID_));
	}

	void CVertexBuffer::unbind() const
{
		AGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0u));
	}

	void CVertexBuffer::create()
	{
		if (bufferID_ != 0u)
			destroy();

		AGL_CALL(glGenBuffers(1u, &bufferID_));
	}

	void CVertexBuffer::destroy()
	{
		AGL_CALL(glDeleteBuffers(1u, &bufferID_));

		size_ = 0u;
		count_ = 0u;
		bufferID_ = 0u;
	}

	void CVertexBuffer::allocate(void const * const data, const std::uint64_t size, const std::uint64_t count)
	{
		AGL_CORE_ASSERT(size != 0u, "Reserving an empty buffer!");
		AGL_CORE_ASSERT(count != 0u, "Count is required!");

		create();
		bind();

		size_ = size;
		count_ = count;

		AGL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	void CVertexBuffer::buffer(void const * const data, const std::uint64_t offset, const std::uint64_t size)
	{
		AGL_CORE_ASSERT(data != nullptr, "Can not set nullptr data!");
		AGL_CORE_ASSERT(offset + size <= getSize(), "Buffer overflow!");

		bind();

		AGL_CALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	}

	std::uint64_t CVertexBuffer::getSize() const
	{
		return size_;
	}

	std::uint64_t CVertexBuffer::getCount() const
	{
		return count_;
	}
}