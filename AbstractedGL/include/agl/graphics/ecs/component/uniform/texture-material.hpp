#pragma once
#include "graphics/ecs/component/texture-material.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct texture_uniform {};

	template <typename TComponent>
	class uniform<texture_uniform, TComponent>
		: public uniform_register<texture_uniform, texture>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		bool bindTexture(const texture_uid &id_texture_2d);

		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_ambient;
		std::int32_t m_diffuse;
		std::int32_t m_specular;
	};

#include "graphics/ecs/component/uniform/texture-material.inl"
}