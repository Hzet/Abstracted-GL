#pragma once
#include "graphics/ecs/component/material.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	template <>
	class uniform<material>
		: public register_uniform<material>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t shininess;
		std::int32_t ambient;
		std::int32_t diffuse;
		std::int32_t specular;
		std::int32_t emission;
	};

#include "graphics/ecs/component/uniform/material.inl"
}