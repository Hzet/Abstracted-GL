#pragma once
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-register.hpp"
#include "agl/graphics/ecs/component/transformable.hpp"
#include "agl/ecs/entity.hpp"

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
		std::int32_t m_transform;
	};

#include "agl/graphics/ecs/component/uniform/transform.inl"
}