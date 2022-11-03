template <typename TComponent>
uniform<direction_uniform, TComponent>::uniform()
	: uniform_register<direction_uniform, direction>{ "direction" }
{
}

template <typename TComponent>
void uniform<direction_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto const& direction = e.get_component<TComponent>();

	s.set_uniform(m_forward, direction.forward);
	s.set_uniform(m_right, direction.right);
	s.set_uniform(m_up, direction.up);
}

template <typename TComponent>
void uniform<direction_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_forward = sh.get_location(get_full_name() + "." + "forward");
	m_right = sh.get_location(get_full_name() + "." + "right");
	m_up = sh.get_location(get_full_name() + "." + "up");

	m_update_uniform_locations = false;
}