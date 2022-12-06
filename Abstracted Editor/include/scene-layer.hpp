#pragma once
#include <glm/glm.hpp>
#include "agl/core/app/layer-base.hpp"
#include "agl/utility/ecs/entity.hpp"
#include "agl/core/misc/timer.hpp"

namespace editor
{
	class scene_layer
		: public agl::layer_base
	{
	public:
		virtual void on_attach() override;
		virtual void on_update() override;

	private:
		agl::entity m_camera_perspective;
		agl::entity m_camera_orthographic;
		agl::entity m_fps_text;
		float m_camera_velocity;
		float m_camera_sensitivity;
		agl::timer m_timer;
		glm::vec2 m_last_mouse_position;
		std::uint64_t m_frame_count;
	};
}