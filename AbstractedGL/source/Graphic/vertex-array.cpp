#include "vertex-array.hpp"

#include "../System/gl-core.hpp"

namespace agl
{
	CVertexArray::CVertexArray()
		: iCount_(0u),
		vCount_(0u)
	{
	}

	CVertexArray::~CVertexArray()
	{
		if (!isMoveConstructing())
			destroy();
	}

	void CVertexArray::bind() const
	{
		AGL_CALL(glBindVertexArray(objectID_));
	}

	void CVertexArray::unbind() const
	{
		AGL_CALL(glBindVertexArray(0u));
	}

	void CVertexArray::create()
	{
		if (isCreated())
			destroy();

		AGL_CALL(glGenVertexArrays(1u, &objectID_));
	}

	void CVertexArray::destroy()
	{
		AGL_CALL(glDeleteVertexArrays(1u, &objectID_));

		objectID_ = 0u;
		iCount_ = 0u;
		vCount_ = 0u;
	}

	void CVertexArray::setBuffer(const CVertexBuffer &vBuffer, const CVertexLayout &layout)
	{
		vCount_ = vBuffer.getCount();

		vBuffer.bind();
		create();
		bind();

		std::uint64_t offset = 0u;

		for (std::uint32_t i = 0u; i < layout.getCount(); i++)
		{
			AGL_CALL(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized, layout.getStride(), reinterpret_cast<void*>(offset)));
			AGL_CALL(glEnableVertexAttribArray(i));
			offset += layout[i].size;
		}
	}

	void CVertexArray::setBuffer(const CVertexBuffer &vBuffer, const CVertexLayout &layout, const CIndexBuffer &iBuffer)
	{
		vCount_ = vBuffer.getCount();
		iCount_ = iBuffer.getCount();
		
		create();

		bind();
		vBuffer.bind();
		iBuffer.bind();

		std::uint64_t offset = 0u;

		for (std::uint32_t i = 0u; i < layout.getCount(); i++)
		{
			AGL_CALL(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized ? GL_TRUE : GL_FALSE, layout.getStride(), reinterpret_cast<void*>(offset)));
			AGL_CALL(glEnableVertexAttribArray(i));
			offset += layout[i].size;
		}
	}

	std::uint32_t CVertexArray::getIndexCount() const
	{
		return iCount_;
	}

	std::uint32_t CVertexArray::getVertexCount() const
	{
		return vCount_;
	}

}