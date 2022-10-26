#pragma once
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-register.hpp"
#include "graphics/ecs/component/camera-orthographic.hpp"
#include "graphics/ecs/component/camera-perspective.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	struct camera_uniform{};

	template <typename TComponent>
	class uniform<camera_uniform, TComponent>
		: public register_uniform<camera_uniform, camera_perspective, camera_orthographic>
	{
	public:
		using register_uniform::register_uniform;

		uniform();

		virtual void send_uniform(const shader &s, const entity &e) override;

	private:
		virtual void update_uniform_locations(shader const& sh) override;

	private:
		std::int32_t m_projection;
		std::int32_t m_view;
	};


	template <typename TComponent>
	uniform<camera_uniform, TComponent>::uniform()
		: register_uniform<camera_uniform, camera_perspective, camera_orthographic>{ "camera" }
	{
	}

	template <typename TComponent>
	void uniform<camera_uniform, TComponent>::send_uniform(const shader &s, const entity &e)
	{
		if (m_update_uniform_locations)
			update_uniform_locations(s);

		auto const& camera = e.get_component<TComponent>();

		s.set_uniform(m_projection, camera.get_projection());
		s.set_uniform(m_view, camera.get_view());
	}

	template <typename TComponent>
	void uniform<camera_uniform, TComponent>::update_uniform_locations(shader const& sh)
	{
		m_projection = sh.get_location(get_name() + get_index() + "." + "projection");
		m_view = sh.get_location(get_name() + get_index() + "." + "view");

		m_update_uniform_locations = false;
	}


#include "graphics/ecs/component/uniform/camera-uniform.inl"
}