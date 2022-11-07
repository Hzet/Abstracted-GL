#pragma once
#include "agl/graphics/render/vertex-array.hpp"
#include "agl/graphics/render/render-type-uid.hpp"
#include "agl/graphics/types/types.hpp"
#include "agl/utility/sorted-vector.hpp"

namespace agl
{
	class render_buffer
	{
	public:
		void bind() const;
		void unbind() const;

		std::uint64_t get_index_count() const;
		std::uint64_t get_index_size() const;

		void set_vertex_count(std::uint64_t count);
		std::uint64_t get_vertex_count() const;
		std::uint64_t get_vertex_size() const;

		std::uint64_t get_stride_count() const;
		std::uint64_t get_stride_size() const;

		std::byte const * const get_vertices() const;
		std::uint32_t const * const get_indices() const;

		void add_indices(const std::vector<std::uint32_t> &data);
		void add_indices(std::uint32_t const * const data, std::uint64_t count);

		template <typename T> void set_vertices(const std::vector<T> &data);
		template <typename T> void set_vertices(const T * const data);

		template <typename T> T& get(std::uint64_t index);
		template <typename T> const T& get(std::uint64_t index) const;

	private:
		template <typename T> std::uint64_t get_offset(std::uint64_t index) const;
		void update_buffers() const;

		std::uint64_t m_vcount;
		std::vector<std::uint32_t> m_indices;
		std::vector<std::byte> m_vertices;
		sorted_vector<render_type_uid, std::uint64_t> m_index_map;

		mutable bool m_require_update;
		mutable index_buffer m_ibuffer;
		mutable vertex_array m_varray;
		mutable vertex_buffer m_vbuffer;
		mutable vertex_layout m_vlayout;
	};

#include "agl/graphics/render/render-buffer.inl"
}

