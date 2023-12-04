template <typename TComponent>
uniform<camera_uniform, TComponent>::uniform()
	: uniform_register<camera_uniform, camera_perspective, camera_orthographic>{ "camera" }
{
}

template <typename TComponent>
void uniform<camera_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_projection = sh.get_location(get_indexed_name() + "." + "projection");
		m_view = sh.get_location(get_indexed_name() + "." + "view");

		// optional
		m_resolution = sh.ask_location(get_indexed_name() + "." + "resolution");

		m_update_uniform_locations = false;
	}

	auto& camera = e.get_component<TComponent>();

	sh.set_uniform(m_projection, camera.calc_projection());
	sh.set_uniform(m_resolution, camera.get_resolution());
	sh.set_uniform(m_view, camera.get_view());
}