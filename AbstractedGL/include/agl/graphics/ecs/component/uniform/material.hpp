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
		std::int32_t m_shininess;
		std::int32_t m_ambient;
		std::int32_t m_diffuse;
		std::int32_t m_specular;
		std::int32_t m_emission;
	};
}