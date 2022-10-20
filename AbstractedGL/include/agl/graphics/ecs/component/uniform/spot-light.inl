template <typename TComponent>
uniform<spot_light_uniform, TComponent>::uniform()
	: register_uniform<spot_light_uniform, spot_light>{ "spot_light" }
{
}

template <typename TComponent>
void uniform<spot_light_uniform, TComponent>::send_uniform(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto const& light = e.get_component<TComponent>();

	s.set_uniform(m_ambient, light.ambient);
	s.set_uniform(m_color, light.color);
	s.set_uniform(m_cut_off, light.cut_off);
	s.set_uniform(m_diffuse, light.diffuse);
	s.set_uniform(m_direction, light.direction);
	s.set_uniform(m_range, light.range);
	s.set_uniform(m_specular, light.specular);
}

template <typename TComponent>
void uniform<spot_light_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_name() + get_index() + "." + "ambient");
	m_color = sh.get_location(get_name() + get_index() + "." + "color");
	m_cut_off = sh.get_location(get_name() + get_index() + "." + "cut_off");
	m_diffuse = sh.get_location(get_name() + get_index() + "." + "diffuse");
	m_direction = sh.get_location(get_name() + get_index() + "." + "direction");
	m_range = sh.get_location(get_name() + get_index() + "." + "range");
	m_specular = sh.get_location(get_name() + get_index() + "." + "specular");

	m_update_uniform_locations = false;
}