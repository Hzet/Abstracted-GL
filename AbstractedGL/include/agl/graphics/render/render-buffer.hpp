#pragma once
#include "agl/core/app/resource-destructor.hpp"
#include "agl/debug/assert.hpp"
#include "agl/graphics/render/vertex-array.hpp"
#include "agl/graphics/render/render-type.hpp"
#include "agl/graphics/types/types.hpp"
#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	class render_buffer
		: public destructive_move
	{
	public:
		~render_buffer();

		std::uint64_t get_index_count() const;
		std::uint64_t get_index_size() const;

		std::uint64_t get_vertex_count() const;
		std::uint64_t get_vertex_size() const;

		std::uint64_t get_stride_count() const;
		std::uint64_t get_stride_size() const;

		gl_buffer_usage get_usage() const;
		void set_usage(gl_buffer_usage usage);

		std::byte const * const get_vertices() const;
		std::uint32_t const * const get_indices() const;

		void clear();

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

		template <typename T> auto& get(std::uint64_t index);
		template <typename T> auto const& get(std::uint64_t index) const;

	private:
		struct array_info
		{
			render_type_uid id_render; // render id
			std::uint64_t array_index; // index in m_array_info / index of destructor in m_destructors
			std::uint64_t type_size;   // size of the stored type
		};

	private:
		template <typename T>
		array_info const& add_vertex_type();

		template <typename T>
		array_info const& get_array_info() const;

		void resize(std::uint64_t new_count);

		template <typename T> std::uint64_t get_offset(std::uint64_t index) const;

	private:
		std::vector<array_info> m_array_info;
		std::vector<std::uint32_t> m_indices;
		std::vector<std::byte> m_vertices;
		std::vector<std::unique_ptr<render_type_destructor_base>> m_destructors;

		std::uint64_t m_vcount;
		bool m_require_update;
		index_buffer m_ibuffer;
		vertex_array m_varray;
		vertex_buffer m_vbuffer;
		vertex_layout m_vlayout;
	};

#include "agl/graphics/render/render-buffer.inl"
}

