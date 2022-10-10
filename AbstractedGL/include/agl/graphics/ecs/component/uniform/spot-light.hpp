#pragma once
#include "graphics/ecs/component/spot-light.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	class uniform<spot_light>
		: public register_uniform<spot_light>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send(const shader &s, const entity &e) override;
	};

#include "graphics/ecs/component/uniform/spot-light.inl"
}