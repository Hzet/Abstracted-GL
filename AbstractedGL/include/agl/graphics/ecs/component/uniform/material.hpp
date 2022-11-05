#pragma once
#include "agl/graphics/ecs/component/material.hpp"
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-register.hpp"
#include "agl/utility/ecs/entity.hpp"

namespace agl
{
	struct material_uniform { };

	template <typename TComponent>
	class uniform<material_uniform, TComponent>
		: public uniform_register<material_uniform, material>
	{
	public:
		using uniform_register::uniform_register;

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

#include "agl/graphics/ecs/component/uniform/material.inl"
}