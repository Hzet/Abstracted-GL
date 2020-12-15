#pragma once

#include <vector>

#include "tuple-buffer-base.hpp"

namespace agl
{
	template <class... Args>
	class CTupleBuffer
		: private impl::CTupleBufferBase<Args...>
	{
	public:
		CTupleBuffer() noexcept;
		explicit CTupleBuffer(Args&&... elems);

		~CTupleBuffer();
		CTupleBuffer(CTupleBuffer&&) = default;

		CTupleBuffer& operator=(CTupleBuffer&&) = default;

		void push_back(Args&&... elems);

		void clear();
		void resize(std::size_t count);

		std::size_t getSize() const;		// size in bytes
		std::size_t getCount() const;		// elements
		std::size_t getStrideSize() const;  // parameter size in bytes
		std::size_t getStrideCount() const; // parameter count

		template <std::size_t I> auto& get(std::size_t index);
		template <std::size_t I> const auto& get(std::size_t index) const;

		std::byte const * const getData() const;

	private:
		template <std::size_t I> auto * const getPointer(std::size_t index);
		template <std::size_t I> auto const * const getPointer(std::size_t index) const;

		template <std::size_t I> std::byte * const getStoragePointer(std::size_t index);
		template <std::size_t I> std::byte const * const getStoragePointer(std::size_t index) const;

		std::vector<std::byte> data_;
	};

#include "tuple-buffer.inl"
}	