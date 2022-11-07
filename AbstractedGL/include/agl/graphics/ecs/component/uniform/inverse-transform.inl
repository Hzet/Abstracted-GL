template <typename TComponent>
uniform<inverse_transform_uniform, TComponent>::uniform()
	: uniform_register<inverse_transform_uniform, transformable>{ "model" }
{
}

template <typename TComponent>
void uniform<inverse_transform_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto &transform = e.get_component<TComponent>();

	s.set_uniform(m_inverse_transform, transform.get_inverse_transform());
}

template <typename TComponent>
void uniform<inverse_transform_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_inverse_transform = sh.get_location(get_full_name() + "." + "inverse_transform");

	m_update_uniform_locations = false;
}