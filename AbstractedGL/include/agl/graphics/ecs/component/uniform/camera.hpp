#pragma once
#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/graphics/shader/uniform-register.hpp"
#include "agl/graphics/ecs/component/camera-orthographic.hpp"
#include "agl/graphics/ecs/component/camera-perspective.hpp"
#include "agl/ecs/entity.hpp"

namespace agl
{
	struct camera_uniform
	{
		shader_uid id_shader;
	};

	template <typename TComponent>
	class uniform<camera_uniform, TComponent>
		: public uniform_register<camera_uniform, camera_perspective, camera_orthographic>
	{
	public:
		using uniform_register::uniform_register;

		uniform();

		virtual void send(const shader &s, const entity &e) override;

	private:
		std::int32_t m_projection;
		std::int32_t m_resolution;
		std::int32_t m_view;
	};

#include "agl/graphics/ecs/component/uniform/camera.inl"
}