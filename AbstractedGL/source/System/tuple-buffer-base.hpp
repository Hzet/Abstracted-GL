#pragma once 

#include <tuple>
#include <cstddef>
#include <type_traits>

namespace agl
{
	template <class... Args> class TTupleBuffer;

	namespace impl
	{
		/// <summary>
		/// Base class for a tuple buffer providing only static methods required
		/// to manage and maintain the buffer's data.
		/// </summary>
		template <class... Args>
		class TTupleBufferBase
		{
			friend class agl::TTupleBuffer<Args...>;

			/// <summary>
			/// Get the size of the stride in bytes.
			/// </summary>
			/// <returns>
			/// The size of the stride
			/// </returns>
			static constexpr std::size_t GetStrideSize();

			/// <summary>
			/// Get the total number of types that this buffer is consisting of.
			/// </summary>
			/// <returns>
			/// The count of the elements in the stride
			/// </returns>
			static constexpr std::size_t GetStrideCount();

			/// <summary>
			/// Check whether 'I' is less than the stride count.
			/// Asserts statically on failure.
			/// </summary>
			template <std::size_t I> static constexpr void CheckRange();

			/// <summary>
			/// Get the size of the 'I'th type in bytes.
 			/// </summary>
			/// <returns>
			/// The type's size
			/// </returns>
			template <std::size_t I> static constexpr std::size_t GetElementSize();

			/// <summary>
			/// Get the offset, in bytes, at which 'I'th type of the buffer can be found.
			/// </summary>
			/// <returns>
			/// The offset.
			/// </returns>
			template <std::size_t I> static constexpr std::size_t GetElementOffset();

			/// <summary>
			/// Recursive implementation of the GetElementOffset method.
			/// </summary>
			/// <returns>
			/// The offset.
			/// </returns>
			template <std::size_t I> static constexpr std::size_t GetElementOffset_impl();

			/// <summary>
			/// Call for a destructor of a destructible 'I'th type 
			/// or assert statically if the object is not one of those.
			/// </summary>
			/// <param name="data">The buffer's stride in which the object resides</param>
			template <std::size_t I> static void DestructElement(std::byte * const data);

			/// <summary>
			/// Allocate and default construct the element of 'I'th type.
			/// </summary>
			/// <param name="data">The buffer's stride in which the object will be constructed</param>
			template <std::size_t I> static void ConstructElement(std::byte * const data);

			/// <summary>
			/// Call for a destructor of every destructible type in the 'data' stride
			/// or assert statically if the any of the objects is not one of those.
			/// </summary>
			/// <param name="data">The buffer's stride in which the objects are residing</param>
			template <std::size_t I = 0u> static void DestructAll(std::byte * const data);

			/// <summary>
			/// Allocate and default construct the elements that the stride consists of.
			/// </summary>
			/// <param name="data">The buffer's stride in which the objects will be constructed</param>
			template <std::size_t I = 0u> static void ConstructAll(std::byte * const data);

			/// <summary>
			/// Construct the elements of 'I'th type from a 'value'.
			/// </summary>
			/// <param name="data">The buffer's stride in which the object will be constructed</param>
			/// <param name="value">The value from which the object will be constructed</param>
			template <std::size_t I, class U> static void ConstructElementValue(std::byte * const data, U &&value);

			/// <summary>
			/// Construct all the elements that the stride consists of from a value.
			/// </summary>
			/// <param name="data">The buffer's stride in which the objects will be constructed</param>
			/// <param name="...elems">The values</param>
			static void ConstructValueAll(std::byte * const data, Args&&... elems);

			/// <summary>
			/// Implementation of ConstructValueAll method.
			/// </summary>
			/// <param name="data">The buffer's stride in which the object will be constructed</param>
			/// <param name="t">the tuple</param>
			template <class Tuple, std::size_t... Sequence> static void ConstructValueAll_impl(std::byte * const data, Tuple &&t, std::index_sequence<Sequence...>);

			/// <summary>
			/// Get the pointer of 'I'th element in a 'data' stride
			/// </summary>
			/// <param name="data">The data from which the pointer will be returned</param>
			/// <returns>
			/// The pointer to the 'I'th type
			/// </returns>
			template <std::size_t I> static auto * const GetPointer(std::byte * const data);

			/// <summary>
			/// Get the pointer of 'I'th element in a 'data' stride
			/// </summary>
			/// <param name="data">The data from which the pointer will be returned</param>
			/// <returns>
			/// The pointer to the 'I'th type
			/// </returns>
			template <std::size_t I> static auto const * const GetPointer(std::byte const * const data);

			static constexpr std::size_t StrideCount_ = sizeof...(Args);
			static constexpr std::size_t StrideSize_ = GetElementOffset<sizeof...(Args)>();
		};

#include "tuple-buffer-base.inl"
	}
}