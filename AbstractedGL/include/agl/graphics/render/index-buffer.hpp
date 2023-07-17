#pragma once
#include <cstdint>
#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	/// <summary>
	/// OpenGL index array abstraction.
	/// </summary>
	class index_buffer
		: private destructive_move
	{
	public:
		using destructive_move::destructive_move;

		/// <summary>
		/// Set the object's state to invalid.
		/// </summary>
		index_buffer();
		
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		index_buffer(index_buffer&&) = default;

		/// <summary>
		/// Destroy the object.
		/// </summary>
		~index_buffer();

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		index_buffer& operator=(index_buffer&&) = default;

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
		/// create OpenGL object.
		/// </summary>
		void create();

		/// <summary>
		/// Delete OpenGL object and reset it to invalid state.
		/// </summary>
		void destroy();

		/// <summary>
		/// Call OpenGL to allocate 'sizeof(uint32_t) * count' bytes of memory for 'count' objects and insert 'data'.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="count">The count</param>
		void allocate(std::uint32_t const * const data, std::uint32_t count);

		/// <summary>
		/// Call OpenGL to insert 'data' of 'sizeof(uint32_t) * count' bytes in the buffer's memory at 'sizeof(uint32_t) * offset'.
		/// </summary>
		/// <param name="data">The data</param>
		/// <param name="offset">The offset in elements</param>
		/// <param name="count">The count</param>
		void buffer(std::uint32_t const * const data, std::uint32_t offset, std::uint32_t count);

		/// <summary>
		/// Get the count of the elements.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::uint32_t get_count() const;

	private:
		std::uint32_t m_count;
		std::uint32_t m_id_object;
	};
}