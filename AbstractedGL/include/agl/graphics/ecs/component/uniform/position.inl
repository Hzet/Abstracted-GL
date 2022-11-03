template <typename TComponent>
uniform<position_uniform, TComponent>::uniform()
	: uniform_register<position_uniform, transformable>{ "position" }
{
}

template <typename TComponent>
void uniform<position_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto const& transform = e.get_component<TComponent>();

	s.set_uniform(m_position, transform.get_position());
}

template <typename TComponent>
void uniform<position_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_position = sh.get_location(get_full_name() + "." + "position");

	m_update_uniform_locations = false;
}