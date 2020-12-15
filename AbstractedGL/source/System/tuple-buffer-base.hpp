#pragma once 

#include <tuple>
#include <cstddef>
#include <type_traits>

namespace agl
{
	template <class... Args> class CTupleBuffer;

	namespace impl
	{
		template <class... Args>
		class CTupleBufferBase
		{
			friend class agl::CTupleBuffer<Args...>;

			static constexpr std::size_t GetStrideSize();
			static constexpr std::size_t GetStrideCount();

			template <std::size_t I> static constexpr void CheckRange();

			template <std::size_t I> static constexpr std::size_t GetElementSize();
			template <std::size_t I> static constexpr std::size_t GetElementOffset();
			template <std::size_t I> static constexpr std::size_t GetElementOffset_impl();

			template <std::size_t I> static void DestructElement(std::byte * const data);
			template <std::size_t I> static void ConstructElement(std::byte * const data);
			template <std::size_t I = 0u> static void DestructAll(std::byte * const data);
			template <std::size_t I = 0u> static void ConstructAll(std::byte * const data);
			template <std::size_t I, class U> static void ConstructElementValue(std::byte * const data, U &&value);
			static void ConstructValueAll(std::byte * const data, Args&&... elems);
			template <class Tuple, std::size_t... Sequence> static void ConstructValueAll_impl(std::byte * const data, Tuple &&t, std::index_sequence<Sequence...>);

			template <std::size_t I> static auto * const GetPointer(std::byte * const data);
			template <std::size_t I> static auto const * const GetPointer(std::byte const * const data);

			static constexpr std::size_t StrideCount_ = sizeof...(Args);
			static constexpr std::size_t StrideSize_ = GetElementOffset<sizeof...(Args)>();
		};

#include "tuple-buffer-base.inl"
	}
}