uniform<directional_light>::uniform()
	: register_uniform<directional_light>{ "directional_light" }
{
}

void uniform<directional_light>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	s.set_uniform(m_ambient, this->data.ambient);
	s.set_uniform(m_color, this->data.color);
	s.set_uniform(m_diffuse, this->data.diffuse);
	s.set_uniform(m_direction, this->data.direction);
	s.set_uniform(m_specular, this->data.specular);
}

void uniform<directional_light>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_name() + "." + "ambient");
	m_color = sh.get_location(get_name() + "." + "color");
	m_diffuse = sh.get_location(get_name() + "." + "diffuse");
	m_direction = sh.get_location(get_name() + "." + "direction");
	m_specular = sh.get_location(get_name() + "." + "specular");

	update_uniform_locations = false;
}
