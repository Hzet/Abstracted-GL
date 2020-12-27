#include "index-buffer.hpp"

#include "../System/gl-core.hpp"

namespace agl
{

	CIndexBuffer::CIndexBuffer()
		: count_(0u)
	{
	}

	CIndexBuffer::~CIndexBuffer()
	{
		if (!isMoveConstructing())
			destroy();
	}

	void CIndexBuffer::bind() const
{
		AGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectID_));
	}

	void CIndexBuffer::unbind() const
{
		AGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u));
	}

	void CIndexBuffer::create()
	{
		if (isCreated())
			destroy();

		AGL_CALL(glGenBuffers(1u, &objectID_));
	}

	void CIndexBuffer::destroy()
	{
		AGL_CALL(glDeleteBuffers(1u, &objectID_));

		objectID_ = 0u;
		count_ = 0u;
	}

	void CIndexBuffer::allocate(std::uint32_t const * const data, std::uint32_t count)
	{
		AGL_CORE_ASSERT(count != 0u, "Can not allocate no memory!");
		AGL_CORE_ASSERT(count_ == 0u, "Overriding previous allocation!");

		create();
		bind();

		count_ = count;
		AGL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_ * sizeof(std::uint32_t), data, GL_STATIC_DRAW));
	}

	void CIndexBuffer::buffer(std::uint32_t const * const data, std::uint32_t offset, std::uint32_t count)
	{
		AGL_CORE_ASSERT(count != 0u, "Buffering data of zero size!");
		AGL_CORE_ASSERT(count_ != 0u, "Buffer has not been allocated yet!");
		AGL_CORE_ASSERT(offset + count < count_, "Overflowing buffer size!");

		bind();
		AGL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(std::uint32_t), count * sizeof(std::uint32_t), data));
	}

	std::uint32_t CIndexBuffer::getCount() const
	{
		return count_;
	}
}