#include "agl/graphics/render/render-buffer.hpp"

namespace agl
{
	void render_buffer::bind() const
	{
		m_varray.bind();
	}

	void render_buffer::unbind() const
	{
		m_varray.unbind();
	}

	bool render_buffer::require_update() const
	{
		return m_require_update;
	}

	std::uint64_t render_buffer::get_vertex_count() const
	{
		return m_vcount;
	}

	std::uint64_t render_buffer::get_vertex_size() const
	{
		return m_vertices.size();
	}

	std::uint64_t render_buffer::get_index_count() const
	{
		return m_indices.size();
	}

	std::uint64_t render_buffer::get_index_size() const
	{
		return m_indices.size() * sizeof(std::uint32_t);
	}

	std::uint64_t render_buffer::get_stride_count() const
	{
		return m_vlayout.get_count();
	}

	std::uint64_t render_buffer::get_stride_size() const
	{
		return m_vlayout.get_size();
	}

	std::byte const * const render_buffer::get_vertices() const
	{
		return m_vertices.data();
	}

	std::uint32_t const * const render_buffer::get_indices() const
	{
		return m_indices.data();
	}

	void render_buffer::reserve(std::uint64_t vertex_count)
	{
		m_require_update = true;

		m_vcount = vertex_count;

		auto const new_count = get_vertex_count() * get_stride_size();
		m_vertices.reserve(new_count);
	}

	void render_buffer::push_index(std::uint32_t index)
	{
		m_require_update = true;

		m_indices.push_back(index);
	}

	std::uint32_t& render_buffer::get_index(std::uint64_t index)
	{
		return m_indices[index];
	}

	std::uint32_t const& render_buffer::get_index(std::uint64_t index) const
	{
		return m_indices[index];
	}

	void render_buffer::update_buffers()
	{
		if (!m_indices.empty())
			m_ibuffer.allocate(m_indices.data(), static_cast<std::uint32_t>(m_indices.size()));

		if (!m_vertices.empty())
			m_vbuffer.allocate(m_vertices.data(), m_vertices.size(), get_vertex_count());

		if (m_ibuffer.is_created())
			m_varray.set_buffer(m_vbuffer, m_vlayout, m_ibuffer);
		else
			m_varray.set_buffer(m_vbuffer, m_vlayout);

		m_require_update = false;
	}
}