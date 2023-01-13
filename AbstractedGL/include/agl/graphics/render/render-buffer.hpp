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

		template <typename T>
		class iterator
		{
		public:
			iterator();
			~iterator();

			iterator& operator++();
			iterator operator++(int) const;
			iterator& operator+=(int);

			iterator& operator--();
			iterator operator--(int) const;
			iterator& operator-=(int);

			typename T::Type& operator*();
			typename T::Type* const operator->();

		private:
			friend class render_buffer;

			friend iterator operator+(int lhs, iterator const& rhs);
			friend iterator operator+(iterator const& lhs, int rhs);
			friend iterator operator-(int lhs, iterator const& rhs);
			friend iterator operator-(iterator const& lhs, int rhs);

			friend bool operator==(iterator const& lhs, iterator const& rhs);
			friend bool operator!=(iterator const& lhs, iterator const& rhs);
			friend bool operator>(iterator const& lhs, iterator const& rhs);
			friend bool operator>=(iterator const& lhs, iterator const& rhs);
			friend bool operator<=(iterator const& lhs, iterator const& rhs);
			friend bool operator<(iterator const& lhs, iterator const& rhs);

		private:
			iterator(std::byte* const buffer, std::uint64_t index, std::uint64_t offset, std::uint64_t stride);

		private:

			std::byte* const m_buffer; 
			std::uint64_t m_index;
			std::uint64_t m_offset;
			std::uint64_t m_stride;
		};

		template <typename T>
		class const_iterator
		{
		public:
			const_iterator();
			~const_iterator();

			const_iterator& operator++();
			const_iterator operator++(int) const;
			const_iterator& operator+=(int);

			const_iterator& operator--();
			const_iterator operator--(int) const;
			const_iterator& operator-=(int);

			typename T::Type const& operator*();
			typename T::Type const* const operator->();

		private:
			friend class render_buffer;

			friend const_iterator operator+(int lhs, const_iterator const& rhs);
			friend const_iterator operator+(const_iterator const& lhs, int rhs);
			friend const_iterator operator-(int lhs, const_iterator const& rhs);
			friend const_iterator operator-(const_iterator const& lhs, int rhs);

			friend bool operator==(const_iterator const& lhs, const_iterator const& rhs);
			friend bool operator!=(const_iterator const& lhs, const_iterator const& rhs);
			friend bool operator>(const_iterator const& lhs, const_iterator const& rhs);
			friend bool operator>=(const_iterator const& lhs, const_iterator const& rhs);
			friend bool operator<=(const_iterator const& lhs, const_iterator const& rhs);
			friend bool operator<(const_iterator const& lhs, const_iterator const& rhs);

		private:
			const_iterator(std::byte* const buffer, std::uint64_t index, std::uint64_t offset, std::uint64_t stride);

		private:

			std::byte* const m_buffer;
			std::uint64_t m_index;
			std::uint64_t m_offset;
			std::uint64_t m_stride;
		};

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

		template <typename T>
		iterator<T> begin();
		template <typename T>
		iterator<T> end(); 

		template <typename T>
		const_iterator<T> cbegin() const;
		template <typename T>
		const_iterator<T> cend() const;

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
			std::uint64_t array_element_count;
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

		std::uint64_t m_vcount;
		bool m_require_update;
		index_buffer m_ibuffer;
		vertex_array m_varray;
		vertex_buffer m_vbuffer;
		vertex_layout m_vlayout;
	};

#include "agl/graphics/render/render-buffer.inl"
}