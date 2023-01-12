#pragma once
#include <cstddef>
#include <cstdint>

namespace agl
{
	template <typename TName>
	class resource_destructor_base
	{
	public:
		virtual ~resource_destructor_base() = default;

		virtual void construct_element(std::byte* const buffer, std::uint64_t count = 1, std::uint64_t offset_to_next = 0) const = 0;
		virtual void destruct_element(std::byte* const data, std::uint64_t count = 1, std::uint64_t offset_to_next = 0) const = 0;
	};

	template <typename TName, typename T>
	class resource_destructor
		: public resource_destructor_base<TName>
	{
	public:
		virtual void construct_element(std::byte* const buffer, std::uint64_t count = 1, std::uint64_t offset_to_next = 0) const override;
		virtual void destruct_element(std::byte* const data, std::uint64_t count = 1, std::uint64_t offset_to_next = 0) const override;
	};

	template <typename TName, typename T>
	void resource_destructor<TName, T>::construct_element(std::byte* const buffer, std::uint64_t count, std::uint64_t offset_to_next) const
	{
		for (auto i = 0u; i < count; ++i)
			new (buffer + i * offset_to_next) T();
	}

	template <typename TName, typename T>
	void resource_destructor<TName, T>::destruct_element(std::byte* const data, std::uint64_t count, std::uint64_t offset_to_next) const
	{
		for (auto i = 0u; i < count; ++i)
		{
			T *ptr = reinterpret_cast<T*>(data + offset_to_next * i);

			ptr->~T();
		}
	}
}

