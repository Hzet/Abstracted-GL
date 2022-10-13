#include "graphics/render/vertex-buffer.hpp"
#include "system/glcore/gl-core.hpp"

namespace agl
{
	vertex_buffer::vertex_buffer()
		: m_size(0u)
		, m_id_object(0u)
		, m_count(0u)
	{
	}

	vertex_buffer::~vertex_buffer()
	{
		if (!is_move_constructing())
			destroy();
	}

	bool vertex_buffer::is_created() const
	{
		return m_id_object != 0u;
	}

	void vertex_buffer::bind() const
{
		AGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id_object));
	}

	void vertex_buffer::unbind() const
{
		AGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0u));
	}

	void vertex_buffer::create()
	{
		if (is_created())
			destroy();

		AGL_CALL(glGenBuffers(1u, &m_id_object));
	}

	void vertex_buffer::destroy()
	{
		AGL_CALL(glDeleteBuffers(1u, &m_id_object));

		m_size = 0u;
		m_count = 0u;
		m_id_object = 0u;
	}

	void vertex_buffer::allocate(void const * const data, const std::uint32_t size, const std::uint32_t count)
	{
		AGL_CORE_ASSERT(size != 0u, "Reserving an empty buffer!");
		AGL_CORE_ASSERT(count != 0u, "Count is required!");

		create();
		bind();

		m_size = size;
		m_count = count;

		AGL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	void vertex_buffer::buffer(void const * const data, const std::uint32_t offset, const std::uint32_t size)
	{
		AGL_CORE_ASSERT(data != nullptr, "Can not set nullptr data!");
		AGL_CORE_ASSERT(offset + size <= get_size(), "Buffer overflow!");

		bind();

		AGL_CALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	}

	std::uint32_t vertex_buffer::get_size() const
	{
		return m_size;
	}

	std::uint32_t vertex_buffer::get_count() const
	{
		return m_count;
	}
}