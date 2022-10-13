#include "graphics/render/index-buffer.hpp"
#include "system/glcore/gl-core.hpp"

namespace agl
{

	index_buffer::index_buffer()
		: m_count(0u)
		, m_id_object(0u)
	{
	}

	index_buffer::~index_buffer()
	{
		if (!is_move_constructing())
			destroy();
	}

	bool index_buffer::is_created() const
	{
		return m_id_object != 0u;
	}

	void index_buffer::bind() const
{
		AGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id_object));
	}

	void index_buffer::unbind() const
{
		AGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u));
	}

	void index_buffer::create()
	{
		if (is_created())
			destroy();

		AGL_CALL(glGenBuffers(1u, &m_id_object));
	}

	void index_buffer::destroy()
	{
		AGL_CALL(glDeleteBuffers(1u, &m_id_object));

		m_id_object = 0u;
		m_count = 0u;
	}

	void index_buffer::allocate(std::uint32_t const * const data, std::uint32_t count)
	{
		AGL_CORE_ASSERT(count != 0u, "Can not allocate no memory!");
		AGL_CORE_ASSERT(m_count == 0u, "Overriding previous allocation!");

		create();
		bind();

		m_count = count;
		AGL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(std::uint32_t), data, GL_STATIC_DRAW));
	}

	void index_buffer::buffer(std::uint32_t const * const data, std::uint32_t offset, std::uint32_t count)
	{
		AGL_CORE_ASSERT(count != 0u, "Buffering data of zero size!");
		AGL_CORE_ASSERT(m_count != 0u, "Buffer has not been allocated yet!");
		AGL_CORE_ASSERT(offset + count < m_count, "Overflowing buffer size!");

		bind();
		AGL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(std::uint32_t), count * sizeof(std::uint32_t), data));
	}

	std::uint32_t index_buffer::get_count() const
	{
		return m_count;
	}
}