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

	render_buffer::~render_buffer()
	{
		if (!is_move_constructing())
			clear();
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

	gl_buffer_usage render_buffer::get_usage() const
	{
		return m_vbuffer.get_usage();
	}

	void render_buffer::set_usage(gl_buffer_usage usage)
	{
		m_vbuffer.set_usage(usage);
	}

	std::byte const * const render_buffer::get_vertices() const
	{
		return m_vertices.data();
	}

	std::uint32_t const * const render_buffer::get_indices() const
	{
		return m_indices.data();
	}

	void render_buffer::clear()
	{
		for (auto i = 0u; i < m_array_info.size(); ++i)
			m_destructors[i]->destruct_element(m_vertices.data() + m_vlayout[i].offset, m_vcount, get_stride_size());

		m_array_info.clear();
		m_indices.clear();
		m_vertices.clear();

		m_vcount = 0;
		m_require_update = false;
		m_ibuffer = index_buffer{};
		m_varray = vertex_array{};
		m_vbuffer = vertex_buffer{};
		m_vlayout = vertex_layout{};
	}

	void render_buffer::resize(std::uint64_t vertex_count)
	{
		if (m_vcount >= vertex_count)
			return;

		m_require_update = true;

		auto const old_count = vertex_count - m_vcount;
		auto const new_size = vertex_count * get_stride_size();
		auto const old_size = old_count * get_stride_size();

		m_vcount = vertex_count;
		m_vertices.resize(new_size);

		for (auto i = 0; i < m_array_info.size(); ++i)
		{
			auto* const buffer = m_vertices.data() + old_size * m_vlayout[i].offset;
			auto const count = vertex_count - old_count;

			m_destructors[i]->construct_element(buffer, count, get_stride_size());
		}
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