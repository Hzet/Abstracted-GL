#pragma once
#include "graphics/ecs/component/spot-light.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct spot_light_uniform{};
	
	template <typename TComponent>
	class uniform<spot_light_uniform, TComponent>
		: public register_uniform<spot_light_uniform, spot_light>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send_uniform(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_ambient;
		std::int32_t m_color;
		std::int32_t m_cut_off; 
		std::int32_t m_diffuse;
		std::int32_t m_direction;
		std::int32_t m_range; 
		std::int32_t m_specular;
	};

#include "graphics/ecs/component/uniform/spot-light.inl"
}