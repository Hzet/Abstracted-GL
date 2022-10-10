#pragma once

namespace agl
{
	template <typename TInherited, typename TData>
	class base_type
		: public TInherited
	{
	public:
		using Type = TData;

		base_type() = default;

		base_type(base_type &&other);
		base_type(const base_type &other);

		template <typename T> base_type(T data);
		template <typename... Args> base_type(Args&&... args);

		base_type& operator=(base_type &&other);
		base_type& operator=(const base_type &other);

		base_type& operator=(TData data);
		template <typename... Args> base_type& operator=(Args&&... args);

		operator TData&();
		operator const TData&() const;

		TData* const operator->();
		const TData* const operator->() const;

	private:
		TData m_data;
	};

#include "graphics/types/type-base.inl"
}