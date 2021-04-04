#pragma once

#include <vector>

#include "tuple-buffer-base.hpp"

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
	class CTupleBuffer
		: private impl::CTupleBufferBase<Args...>
	{
	public:
		/// <summary>
		/// Construct no elements, set the 'size_' to 0.
		/// </summary>
		CTupleBuffer() noexcept;

		/// <summary>
		/// Construct only the first stride from variadic template parameters which is damn broken to me.
		/// TODO: make it bracket initiallizable in the future - you should not use this method yet.
		/// </summary>
		/// <param name="...elems"></param>
		//CTupleBuffer(Args&&... elems);

		/// <summary>
		/// Destruct all the elements contained by the buffer.
		/// </summary>
		~CTupleBuffer();
		
		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CTupleBuffer(CTupleBuffer&&) = default;

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		CTupleBuffer(const CTupleBuffer&) = default;

		/// <summary>
		/// Default move assignment.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CTupleBuffer& operator=(CTupleBuffer&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CTupleBuffer& operator=(const CTupleBuffer&) = default;

		/// <summary>
		/// Push back a stride.
		/// </summary>
		/// <param name="...elems">Elements of the stride</param>
		void push_back(Args&&... elems);

		/// <summary>
		/// Destruct all the data contained by the buffer and set the 'size_' to zero.
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
		std::size_t getSize() const;

		/// <summary>
		/// Get the count of the strides contained by the buffer.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::size_t getCount() const;

		/// <summary>
		/// Get the size of the stride in bytes.
		/// </summary>
		/// <returns>
		/// The size
		/// </returns>
		std::size_t getStrideSize() const;

		/// <summary>
		/// Get the count of types in the stride.
		/// </summary>
		/// <returns>
		/// The count
		/// </returns>
		std::size_t getStrideCount() const; // parameter count

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
		/// Get the pointer to the 'data_'.
		/// </summary>
		/// <returns>
		/// The pointer
		/// </returns>
		std::byte const * const getData() const;

	private:
		/// <summary>
		/// Get the pointer to 'index'th element of 'I'th type.
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The pointer
		/// </returns>
		template <std::size_t I> auto * const getPointer(std::size_t index);
		

		template <std::size_t I> auto const * const getPointer(std::size_t index) const;

		/// <summary>
		/// Get the 'data_' pointer to 'index'th element of 'I'th type.
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The pointer
		/// </returns>
		template <std::size_t I> std::byte * const getStoragePointer(std::size_t index);

		/// <summary>
		/// Get the 'data_' pointer to 'index'th element of 'I'th type.
		/// </summary>
		/// <param name="index">The position in strides</param>
		/// <returns>
		/// The pointer
		/// </returns>
		template <std::size_t I> std::byte const * const getStoragePointer(std::size_t index) const;

		std::vector<std::byte> data_;
	};

#include "tuple-buffer.inl"
}	