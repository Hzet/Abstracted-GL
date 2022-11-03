#pragma once
#include "graphics/ecs/component/transformable.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct position_uniform {};

	template <typename TComponent>
	class uniform<position_uniform, TComponent>
		: public uniform_register<position_uniform, transformable>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_position;
	};

#include "graphics/ecs/component/uniform/position.inl"
}