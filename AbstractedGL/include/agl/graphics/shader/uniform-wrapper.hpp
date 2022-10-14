#pragma once
#include "graphics/shader/uniform-data.hpp"
#include "graphics/shader/uniform.hpp"

namespace agl
{
	class uniform_wrapper_base
	{
	public:
		virtual std::unique_ptr<uniform_base> clone(uniform_base const * const dataSource = nullptr) const = 0;

		const uniform_base& get_uniform() const;

	protected:
		std::unique_ptr<uniform_base> m_uniform;
	};

	template <typename TData, typename TComponent>
	class uniform_wrapper final
		: public uniform_wrapper_base
	{
	public:
		uniform_wrapper();

		virtual std::unique_ptr<uniform_base> clone(uniform_base const * const dataSource = nullptr) const override;
	};

#include "graphics/shader/uniform-wrapper.inl"
}