#pragma once
#include <cstdint>
#include "agl/system/glcore/destructive-move.hpp"
#include "agl/core/enums/gl-buffer-usage-type.hpp"

namespace agl
{
	/// <summary>
	/// OpenGL vertex buffer abstraction.
	/// </summary>
	class vertex_buffer
		: private destructive_move
	{
	public:
		using destructive_move::destructive_move;

		/// <summary>
		/// Set the object's state to invalid.
		/// </summary>
		vertex_buffer();

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		vertex_buffer(vertex_buffer&&) = default;

		/// <summary>
		/// Destroy the object and set it's state to invalid.
		/// </summary>
		~vertex_buffer();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		vertex_buffer& operator=(vertex_buffer&&) = default;

		/// <summary>
		/// Check whether this object's status is active.
		/// </summary>
		/// <returns>
		/// True - object is a valid OpenGL object
		/// False - object is not a valid OpenGL object
		/// </returns>
		bool is_created() const;

		/// <summary>
		/// Bind OpenGL object to the current context.
		/// </summary>
		void bind() const;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		void unbind() const;

		/// <summary>
		/// Generate OpenGL object.
		/// </summary>
		void create();

		/// <summary>
		/// Delete OpenGL object and reset it to invalid state.
		/// </summary>
		void destroy();

		/// <summary>
		/// Call OpenGL to allocate 'size' bytes of memory for 'count' objects and insert 'data'.
		/// Assert on failure.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="size">The size</param>
		/// <param name="count">The count</param>
		void allocate(void const * const data, const std::uint32_t size, const std::uint32_t count); // data, overall size, vertex count (amount of strides)

		/// <summary>
		/// Call OpenGL to insert 'data' of 'size' bytes in the buffer's memory at 'offset'.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="offset">The offset</param>
		/// <param name="size">The size</param>
		void buffer(void const * const data, const std::uint32_t offset, const std::uint32_t size);

		gl_buffer_usage get_usage() const;
		void set_usage(gl_buffer_usage usage);

		/// <summary>
		/// Get the size of the memory allocated for this buffer in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </returns>
		std::uint32_t get_size() const;

		/// <summary>
		/// Get the count of vertices that this buffer contains.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t get_count() const;

	private:
		std::uint32_t m_count;
		std::uint32_t m_id_object;
		std::uint32_t m_size;
		gl_buffer_usage m_usage;
	};

}