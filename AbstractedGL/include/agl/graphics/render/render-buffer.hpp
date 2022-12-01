#pragma once
#include "agl/system/debug/assert.hpp"
#include "agl/graphics/render/vertex-array.hpp"
#include "agl/graphics/render/render-type-uid.hpp"
#include "agl/graphics/types/types.hpp"

namespace agl
{
	class render_buffer
	{
	public:
		std::uint64_t get_index_count() const;
		std::uint64_t get_index_size() const;

		std::uint64_t get_vertex_count() const;
		std::uint64_t get_vertex_size() const;

		std::uint64_t get_stride_count() const;
		std::uint64_t get_stride_size() const;

		std::byte const * const get_vertices() const;
		std::uint32_t const * const get_indices() const;

		void bind() const;
		void unbind() const;

		bool require_update() const;
		void update_buffers();

		template <typename T>
		bool has_vertex_type() const;

		template <typename TForwardIterator>
		void push_indices(TForwardIterator begin, TForwardIterator end);
		void push_index(std::uint32_t index);

		template <typename T> void push_vertex(T vertex);
		template <typename T, typename TForwardIterator> 
		void push_vertices(TForwardIterator begin, TForwardIterator end);

		std::uint32_t& get_index(std::uint64_t index);
		std::uint32_t const& get_index(std::uint64_t index) const;

		template <typename T> T& get(std::uint64_t index);
		template <typename T> const T& get(std::uint64_t index) const;

	private:
		struct array_info
		{
			render_type_uid id_render;
			std::uint64_t array_index;
			std::uint64_t array_size;
		};

	private:
		template <typename T>
		array_info const& add_vertex_type();

		template <typename T>
		array_info const& get_array_info() const;

		void reserve(std::uint64_t new_count);

		template <typename T> std::uint64_t get_offset(std::uint64_t index) const;

	private:
		std::vector<array_info> m_array_indexes;
		std::vector<std::uint32_t> m_indices;
		std::vector<std::byte> m_vertices;

		std::uint64_t m_vcount;
		bool m_require_update;
		index_buffer m_ibuffer;
		vertex_array m_varray;
		vertex_buffer m_vbuffer;
		vertex_layout m_vlayout;
	};

#include "agl/graphics/render/render-buffer.inl"
}

