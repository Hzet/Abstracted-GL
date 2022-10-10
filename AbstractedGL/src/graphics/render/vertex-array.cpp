#include "graphics/render/vertex-array.hpp"
#include "system/glcore/gl-core.hpp"

namespace agl
{
	vertex_array::vertex_array()
		: m_icount(0u),
		m_vcount(0u)
	{
	}

	vertex_array::~vertex_array()
	{
		if (!is_move_constructing())
			destroy();
	}

	void vertex_array::bind() const
	{
		AGL_CALL(glBindVertexArray(m_id_object));
	}

	void vertex_array::unbind() const
	{
		AGL_CALL(glBindVertexArray(0u));
	}

	void vertex_array::create()
	{
		if (is_created())
			destroy();

		AGL_CALL(glGenVertexArrays(1u, &m_id_object));
	}

	void vertex_array::destroy()
	{
		AGL_CALL(glDeleteVertexArrays(1u, &m_id_object));

		m_id_object = 0u;
		m_icount = 0u;
		m_vcount = 0u;
	}

	void vertex_array::set_buffer(const vertex_buffer &vBuffer, const vertex_layout &layout)
	{
		m_vcount = vBuffer.get_count();

		vBuffer.bind();
		create();
		bind();

		auto offset = 0u;

		for (auto i = 0u; i < layout.get_count(); i++)
		{
			AGL_CALL(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized, layout.get_size(), reinterpret_cast<void*>(offset)));
			AGL_CALL(glEnableVertexAttribArray(i));
			offset += layout[i].size;
		}
	}

	void vertex_array::set_buffer(const vertex_buffer &vBuffer, const vertex_layout &layout, const index_buffer &iBuffer)
	{
		m_vcount = vBuffer.get_count();
		m_icount = iBuffer.get_count();
		
		create();

		bind();
		vBuffer.bind();
		iBuffer.bind();

		auto offset = 0u;

		for (auto i = 0u; i < layout.get_count(); i++)
		{
			AGL_CALL(glVertexAttribPointer(i, layout[i].count, layout[i].type, layout[i].normalized ? GL_TRUE : GL_FALSE, layout.get_size(), reinterpret_cast<void*>(offset)));
			AGL_CALL(glEnableVertexAttribArray(i));
			offset += layout[i].size;
		}
	}

	std::uint32_t vertex_array::get_index_count() const
	{
		return m_icount;
	}

	std::uint32_t vertex_array::get_vertex_count() const
	{
		return m_vcount;
	}

}