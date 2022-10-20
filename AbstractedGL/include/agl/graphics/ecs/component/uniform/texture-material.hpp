#pragma once
#include "graphics/ecs/component/texture-material.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct texture_material_uniform{};

	template <typename TComponent>
	class uniform<texture_material_uniform, TComponent>
		: public register_uniform<texture_material_uniform, texture_material>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send_uniform(const shader &s, const entity &e) override;

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