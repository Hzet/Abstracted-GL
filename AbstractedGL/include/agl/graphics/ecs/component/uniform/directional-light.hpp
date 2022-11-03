#pragma once
#include "graphics/ecs/component/directional-light.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

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
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_ambient;
		std::int32_t m_color;
		std::int32_t m_diffuse;
		std::int32_t m_specular;
	};

#include "graphics/ecs/component/uniform/directional-light.inl"
}