template <typename TComponent>
uniform<direction_uniform, TComponent>::uniform()
	: register_uniform<directional_light>{ "direction" }
{
}

template <typename TComponent>
void uniform<direction_uniform, TComponent>::send_uniform(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto const& direction = e.get_component<TComponent>();

	s.set_uniform(m_direction, direction);
}

template <typename TComponent>
void uniform<direction_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_direction = sh.get_location(get_name() + get_index() + "." + "direction");

	m_update_uniform_locations = false;
}