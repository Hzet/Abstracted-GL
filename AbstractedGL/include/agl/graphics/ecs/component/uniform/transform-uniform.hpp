#pragma once
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/ecs/component/transformable.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct transform_uniform
	{
	};

	template <typename TComponent>
	class uniform<transform_uniform, TComponent>
		: public uniform_register<transform_uniform, transformable>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_transform;
	};

#include "graphics/ecs/component/uniform/transform-uniform.inl"
}