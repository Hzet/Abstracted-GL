#pragma once
#include "graphics/ecs/component/directional-light.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	template <>
	class uniform<directional_light>
		: public register_uniform<directional_light>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send(const shader &s, const entity &e) override;
	};

#include "graphics/ecs/component/uniform/directional-light.inl"
}