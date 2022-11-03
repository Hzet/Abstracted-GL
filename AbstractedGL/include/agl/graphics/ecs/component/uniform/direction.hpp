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
		: public uniform_register<direction_uniform, direction>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_forward;
		std::int32_t m_right;
		std::int32_t m_up;
	};

#include "graphics/ecs/component/uniform/direction.inl"
}