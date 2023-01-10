#pragma once
#include "agl/graphics/ecs/component/directional-light.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-register.hpp"
#include "agl/ecs/entity.hpp"

namespace agl
{
	struct directional_light_uniform {};

	template <typename TComponent>
	class uniform<directional_light_uniform, TComponent>
		: public uniform_register<directional_light_uniform, directional_light>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		std::int32_t m_ambient;
		std::int32_t m_color;
		std::int32_t m_diffuse;
		std::int32_t m_specular;
	};

#include "agl/graphics/ecs/component/uniform/directional-light.inl"
}