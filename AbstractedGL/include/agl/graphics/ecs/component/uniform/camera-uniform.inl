template <typename TComponent>
uniform<camera_uniform, TComponent>::uniform()
{
	set_name("camera");
}

template <typename TComponent>
void uniform<camera_uniform, TComponent>::send(const shader &s, const entity &e)
{
	auto const& camera = e.get_component<TComponent>();

	s.set_uniform(get_name() + "projection", camera.get_projection());
	s.set_uniform(get_name() + "view", camera.get_view());
}