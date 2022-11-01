#pragma once
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/ecs/component/transformable.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct inverse_transform_uniform
	{
	};

	template <typename TComponent>
	class uniform<inverse_transform_uniform, TComponent>
		: public uniform_register<inverse_transform_uniform, transformable>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_inverse_transform;
	};

#include "graphics/ecs/component/uniform/inverse-transform-uniform.inl"
}
