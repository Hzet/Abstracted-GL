template <typename TComponent>
uniform<direction_uniform, TComponent>::uniform()
	: uniform_register<direction_uniform, direction>{ "direction" }
{
}

template <typename TComponent>
void uniform<direction_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_forward = sh.get_location(get_full_name() + "." + "forward");
		m_right = sh.get_location(get_full_name() + "." + "right");
		m_up = sh.get_location(get_full_name() + "." + "up");

		m_update_uniform_locations = false;
	}

	auto const& direction = e.get_component<TComponent>();

	sh.set_uniform(m_forward, direction.forward);
	sh.set_uniform(m_right, direction.right);
	sh.set_uniform(m_up, direction.up);
}
