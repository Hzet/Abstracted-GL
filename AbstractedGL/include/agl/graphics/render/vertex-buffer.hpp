#pragma once
#include "system/glcore/gl-object.hpp"

namespace agl
{
	/// <summary>
	/// OpenGL vertex buffer abstraction.
	/// </summary>
	class vertex_buffer final
		: public gl_object
	{
	public:
		using gl_object::gl_object;

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
		/// Bind OpenGL object to the current context.
		/// </summary>
		virtual void bind() const override;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		virtual void unbind() const override;

		/// <summary>
		/// Generate OpenGL object.
		/// </summary>
		virtual void create() override;

		/// <summary>
		/// Delete OpenGL object and reset it to invalid state.
		/// </summary>
		virtual void destroy() override;

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
		std::uint32_t m_size;
		std::uint32_t m_count;
	};

}