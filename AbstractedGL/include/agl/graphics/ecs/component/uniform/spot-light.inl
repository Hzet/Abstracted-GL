template <typename TComponent>
uniform<spot_light_uniform, TComponent>::uniform()
	: uniform_register<spot_light_uniform, spot_light>{ "spot_light" }
{
}

template <typename TComponent>
void uniform<spot_light_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);
	
	s.set_uniform(m_ambient, this->data.ambient);
	s.set_uniform(m_color, this->data.color);
	s.set_uniform(m_cut_off, this->data.cut_off);
	s.set_uniform(m_diffuse, this->data.diffuse);
	s.set_uniform(m_direction, this->data.direction);
	s.set_uniform(m_range, this->data.range);
	s.set_uniform(m_specular, this->data.specular);
}

template <typename TComponent>
void uniform<spot_light_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_name() + "." + "ambient");
	m_color = sh.get_location(get_name() + "." + "color");
	m_cut_off = sh.get_location(get_name() + "." + "cut_off");
	m_diffuse = sh.get_location(get_name() + "." + "diffuse");
	m_direction = sh.get_location(get_name() + "." + "direction");
	m_range = sh.get_location(get_name() + "." + "range");
	m_specular = sh.get_location(get_name() + "." + "specular");

	m_update_uniform_locations = false;
}
