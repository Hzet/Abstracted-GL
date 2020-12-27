#pragma once

#include "../System/gl-object.hpp"

namespace agl
{
	/// <summary>
	/// OpenGL vertex buffer abstraction.
	/// </summary>
	class CVertexBuffer final
		: public system::IGLObject
	{
	public:
		using system::IGLObject::IGLObject;

		/// <summary>
		/// Set the object's state to invalid.
		/// </summary>
		CVertexBuffer();

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CVertexBuffer(CVertexBuffer&&) = default;

		/// <summary>
		/// Destroy the object and set it's state to invalid.
		/// </summary>
		~CVertexBuffer();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CVertexBuffer& operator=(CVertexBuffer&&) = default;

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
		void allocate(void const * const data, const std::uint64_t size, const std::uint64_t count); // data, overall size, vertex count (amount of strides)

		/// <summary>
		/// Call OpenGL to insert 'data' of 'size' bytes in the buffer's memory at 'offset'.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="offset">The offset</param>
		/// <param name="size">The size</param>
		void buffer(void const * const data, const std::uint64_t offset, const std::uint64_t size);

		/// <summary>
		/// Get the size of the memory allocated for this buffer in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </returns>
		std::uint64_t getSize() const;

		/// <summary>
		/// Get the count of vertices that this buffer contains.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint64_t getCount() const;

	private:
		std::uint64_t size_;
		std::uint64_t count_;
	};

}