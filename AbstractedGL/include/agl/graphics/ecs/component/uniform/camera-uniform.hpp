#pragma once
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/ecs/component/camera-orthographic.hpp"
#include "graphics/ecs/component/camera-perspective.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct camera_uniform
	{
		shader_uid id_shader;
	};

	template <typename TComponent>
	class uniform<camera_uniform, TComponent>
		: public register_uniform<camera_uniform, camera_perspective, camera_orthographic>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_projection;
		std::int32_t m_view;
	};

#include "graphics/ecs/component/uniform/camera-uniform.inl"
}