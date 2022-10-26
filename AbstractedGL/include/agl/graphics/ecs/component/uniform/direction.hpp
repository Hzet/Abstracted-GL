#pragma once
#include "graphics/ecs/component/direction.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct direction_uniform {};

	template <typename TComponent>
	class uniform<direction_uniform, TComponent>
		: public register_uniform<direction_uniform, direction>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send_uniform(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_direction;
	};

#include "graphics/ecs/component/uniform/directional-light.inl"
}