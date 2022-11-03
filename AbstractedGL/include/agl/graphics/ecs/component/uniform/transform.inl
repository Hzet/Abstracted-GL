template <typename TComponent>
uniform<transform_uniform, TComponent>::uniform()
	: uniform_register<transform_uniform, transformable>{ "model" }
{
}

template <typename TComponent>
void uniform<transform_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto const& transform = e.get_component<TComponent>();

	s.set_uniform(m_transform, transform.get_transform());
}

template <typename TComponent>
void uniform<transform_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_transform = sh.get_location(get_full_name() + "." + "transform");

	m_update_uniform_locations = false;
}