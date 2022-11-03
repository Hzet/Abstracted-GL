#include "graphics/ecs/system/camera-system.hpp"
#include "graphics/ecs/component/camera-perspective.hpp"
#include "graphics/ecs/component/camera-orthographic.hpp"
#include "graphics/ecs/component/transformable.hpp"
#include "graphics/shader/uniform-array.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	void camera_system::init(registry &reg)
	{
	}

	void camera_system::update(registry &reg)
	{
		static auto camera_perspective_view = reg.inclusive_view<camera_perspective, transformable, direction>();
		static auto camera_orthographic_view = reg.inclusive_view<camera_orthographic, transformable, direction>();
		
		if(camera_perspective_view.needs_update())
			camera_perspective_view = reg.inclusive_view<camera_perspective, transformable, direction>();
		
		if (camera_orthographic_view.needs_update())
			camera_orthographic_view = reg.inclusive_view<camera_orthographic, transformable, direction>();

		for (auto it = camera_orthographic_view.cbegin(); it != camera_orthographic_view.cend(); ++it)
		{
			auto const& e = reg.get_entity(*it);
			auto& camera = reg.get<camera_orthographic>(*it);
			auto& transform = reg.get<transformable>(*it);
			auto& dir = reg.get<direction>(*it);
			auto& uniforms = reg.get<uniform_array>(*it);

			if (transform.needs_update())
				camera.update(transform, dir);

			uniforms.send(e);
		}

		for (auto it = camera_perspective_view.cbegin(); it != camera_perspective_view.cend(); ++it)
		{
			auto const& e = reg.get_entity(*it);
			auto& camera = reg.get<camera_perspective>(*it);
			auto& transform = reg.get<transformable>(*it);
			auto& dir = reg.get<direction>(*it);
			auto& uniforms = reg.get<uniform_array>(*it);

			if (transform.needs_update())
				camera.update(transform, dir);

			uniforms.send(e);
		}
	}
}