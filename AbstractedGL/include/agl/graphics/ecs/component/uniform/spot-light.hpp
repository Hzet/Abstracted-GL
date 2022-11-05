#pragma once
#include "agl/graphics/ecs/component/spot-light.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-register.hpp"
#include "agl/utility/ecs/entity.hpp"

namespace agl
{
	struct spot_light_uniform {};

	template <typename TComponent>
	class uniform<spot_light_uniform, TComponent>
		: public uniform_register<spot_light_uniform, spot_light>
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
		std::int32_t m_cut_off; 
		std::int32_t m_diffuse;
		std::int32_t m_range; 
		std::int32_t m_specular;
	};

#include "agl/graphics/ecs/component/uniform/spot-light.inl"
}