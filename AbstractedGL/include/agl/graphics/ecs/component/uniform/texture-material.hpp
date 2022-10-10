#pragma once
#include "graphics/ecs/component/texture-material.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	class uniform<texture>
		: public register_uniform<texture>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		bool bindTexture(const texture_uid &id_texture_2d);
	};

#include "graphics/ecs/component/uniform/texture-material.inl"
}