#pragma once
#include <cstddef>

namespace agl
{
	class resource_destructor_base
	{
	public:
		virtual ~resource_destructor_base() = default;

		virtual void destruct_element(std::byte* const data) const = 0;
	};

	template <typename T>
	class resource_destructor
		: public resource_destructor_base
	{
	public:
		virtual void destruct_element(std::byte* const data) const override;
	};

	template <typename T>
	void resource_destructor<T>::destruct_element(std::byte* const data) const
	{
		T *ptr = reinterpret_cast<T*>(data);

		ptr->~T();
	}
}

