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
		m_projection = sh.get_location(get_full_name() + "." + "projection");
		m_view = sh.get_location(get_full_name() + "." + "view");

		m_update_uniform_locations = false;
	}

	auto const& camera = e.get_component<TComponent>();

	sh.set_uniform(m_projection, camera.get_projection());
	sh.set_uniform(m_view, camera.get_view());
}