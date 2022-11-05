#include "agl/graphics/render/render-buffer.hpp"

namespace agl
{
	void render_buffer::bind() const
	{
		if (m_require_update)
			update_buffers();

		m_varray.bind();
	}

	void render_buffer::unbind() const
	{
		m_varray.unbind();
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

	void render_buffer::set_vertex_count(std::uint64_t count)
	{
		m_require_update = true;

		m_vcount = count;
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

	void render_buffer::add_indices(const std::vector<std::uint32_t> &data)
	{
		m_require_update = true;

		m_indices = data;
	}

	void render_buffer::add_indices(std::uint32_t const * const data, std::uint64_t count)
	{
		m_require_update = true;

		m_indices.resize(count);

		for (auto i = 0ul; i < m_indices.size(); i++)
			m_indices[i] = *(data + i);
	}

	void render_buffer::update_buffers() const
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