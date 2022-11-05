#pragma once
#include <vector>

#include "agl/utility/tuple-buffer-base.hpp"

namespace agl
{
	/// <summary>
	/// A buffer that can store different types like the std::tuple, but the data is contiguous 
	/// and aligned in the same order as the template types are provided. 
	/// The size of the buffer represents the size in bytes
	/// and the count of the buffer related to the count of the strides,
	/// so the total count of the elements is always the count multiplied by the count of types in the stride.
	/// The buffer is a crossover the std::vector and std::tuple.
	/// </summary>
	template <class... Args>
	class tuple_buffer
		: private tuple_buffer_base<Args...>
	{
	public:
		/// <summary>
		/// Construct no elements, set the 'm_size' to 0.
		/// </summary>
		tuple_buffer() noexcept;

		/// <summary>
		/// Construct only the first stride from variadic template parameters which is damn broken to me.
		/// TODO: make it bracket initiallizable in the future - you should not use this method yet.
		/// </summary>
		/// <param name="...elems"></param>
		//CTupleBuffer(Args&&... elems);

		/// <summary>
		/// Destruct all the elements contained by the buffer.
		/// </summary>
		~tuple_buffer();
		
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		tuple_buffer(tuple_buffer&&) = default;

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		tuple_buffer(const tuple_buffer&) = default;

		/// <summary>
		/// Default move assignment.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		tuple_buffer& operator=(tuple_buffer&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		tuple_buffer& operator=(const tuple_buffer&) = default;

		/// <summary>
		/// Push back a stride.
		/// </summary>
		/// <param name="...elems">Elements of the stride</param>
		void push_back(Args&&... elems);

		/// <summary>
		/// Destruct all the data contained by the buffer and set the 'm_size' to zero.
		/// </summary>
		void clear();

		/// <summary>
		/// Resize the container to be capable of containing 'count' strides. 
		/// 
		/// </summary>
		/// <param name="count"></param>
		void resize(std::size_t count);

		/// <summary>
		/// Get the size of the data contained by the buffer in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </returns>
		std::size_t get_size() const;

		/// <summary>
		/// Get the count of the strides contained by the buffer.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::size_t get_count() const;

		/// <summary>
		/// Get the size of the stride in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </returns>
		std::size_t get_stride_size() const;

		/// <summary>
		/// Get the count of types in the stride.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::size_t get_stride_count() const; // parameter count

		/// <summary>
		/// Get the element from 'index'th stride of 'I'th type
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The element
		/// </returns>
		template <std::size_t I> auto& get(std::size_t index);
		
		/// <summary>
		/// Get the element from 'index'th stride of 'I'th type
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The element
		/// </returns>
		template <std::size_t I> const auto& get(std::size_t index) const;

		/// <summary>
		/// Get the pointer to the 'm_data'.
		/// </summary>
		/// <returns>
		/// The pointer
		/// </returns>
		std::byte const * const get_data() const;

	private:
		/// <summary>
		/// Get the pointer to 'index'th element of 'I'th type.
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The pointer
		/// </returns>
		template <std::size_t I> auto * const get_pointer(std::size_t index);
		

		template <std::size_t I> auto const * const get_pointer(std::size_t index) const;

		/// <summary>
		/// Get the 'm_data' pointer to 'index'th element of 'I'th type.
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The pointer
		/// </returns>
		template <std::size_t I> std::byte * const get_storage_pointer(std::size_t index);

		/// <summary>
		/// Get the 'm_data' pointer to 'index'th element of 'I'th type.
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The pointer
		/// </returns>
		template <std::size_t I> std::byte const * const get_storage_pointer(std::size_t index) const;

		std::vector<std::byte> m_data;
	};

#include "agl/utility/tuple-buffer.inl"
}	