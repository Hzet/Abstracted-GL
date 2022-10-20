#pragma once
#include "graphics/shader/uniform.hpp"
#include "graphics/shader/uniform-base.hpp"
#include "graphics/shader/uniform-group.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	template <typename TName>
	class uniform_type
	{
	public:
		uniform_type() = default;
		uniform_type(uniform_type&&) = default;
		uniform_type(uniform_type const& other);
		uniform_type& operator=(uniform_type&&) = default;
		uniform_type& operator=(uniform_type const& other);

		bool need_update(entity const& e) const;

		operator uniform_base&();
		operator uniform_base const&() const;

		uniform_base* const operator->();
		uniform_base const* const operator->() const;

		uniform_base& operator*();
		uniform_base const& operator*() const;

	private:
		void update(entity const& e);

	private:
		std::unique_ptr<uniform_base> m_uniform;
	};


	template <typename TName>
	uniform_type<TName>::uniform_type(uniform_type const& other)
		: m_uniform{ uniform_prototyper::get_prototype(other->get_type_uid(), other->get_component_type_uid(), other.m_uniform()) }
	{
	}

	template <typename TName>
	uniform_type<TName>& uniform_type<TName>::operator=(uniform_type const& other)
	{
		m_uniform = uniform_prototyper::get_prototype(other->get_type_uid(), other->get_component_type_uid(), other.m_uniform());
	}

	template <typename TName>
	bool uniform_type<TName>::need_update(entity const& e) const
	{
		return !e.has_component(m_uniform->get_component_type_uid());
	}

	template <typename TName>
	uniform_type<TName>::operator uniform_base&()
	{
		return *m_uniform;
	}

	template <typename TName>
	uniform_type<TName>::operator uniform_base const&() const
	{
		return *m_uniform;
	}

	template <typename TName>
	uniform_base* const uniform_type<TName>::operator->()
	{
		return m_uniform.get();
	}

	template <typename TName>
	uniform_base const* const uniform_type<TName>::operator->() const
	{
		return m_uniform.get();
	}

	template <typename TName>
	uniform_base& uniform_type<TName>::operator*()
	{
		return *m_uniform;
	}

	template <typename TName>
	uniform_base const& agl::uniform_type<TName>::operator*() const
	{
		return *m_uniform;
	}

	template <typename TName>
	void uniform_type<TName>::update(entity const& e)
	{
		auto const components = uniform_prototyper::get_prototype_components(TUniformDataTypeUID<TName>::value());

		for (auto const index : components)
			if (e.has_component(index))
				m_uniform = uniform_prototyper::get_prototype(TUniformDataTypeUID<TName>::value(), index, m_uniform.get());
	}
}

