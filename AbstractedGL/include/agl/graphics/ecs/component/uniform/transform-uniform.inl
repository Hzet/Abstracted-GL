template <typename TComponent>
uniform<transform_uniform, TComponent>::uniform()
	: register_uniform<transform_uniform, transformable>{ "model" }
{
}

template <typename TComponent>
void uniform<transform_uniform, TComponent>::send_uniform(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto &transform = e.get_component<TComponent>();
	s.set_uniform(m_transform, transform.get_transform());
}

template <typename TComponent>
void uniform<transform_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_transform = sh.get_location(get_name() + get_index() + "." + "transform");

	m_update_uniform_locations = false;
}