template <typename TComponent>
uniform<position_uniform, TComponent>::uniform()
	: uniform_register<position_uniform, transformable>{ "position" }
{
}

template <typename TComponent>
void uniform<position_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_position = sh.get_location(get_indexed_name() + "." + "position");

		m_update_uniform_locations = false;
	}

	auto const& transform = e.get_component<TComponent>();

	sh.set_uniform(m_position, transform.get_position());
}
