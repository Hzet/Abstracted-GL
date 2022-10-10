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
		: public register_uniform<inverse_transform_uniform, transformable>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send(const shader &s, const entity &e) override;
	};

#include "graphics/ecs/component/uniform/inverse-transform-uniform.inl"
}
