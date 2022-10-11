uniform<material>::uniform()
	: register_uniform<material>{ "material" }
{
}

void uniform<material>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);
	
	s.set_uniform(m_shininess, this->data.shininess);
	s.set_uniform(m_ambient, this->data.ambient);
	s.set_uniform(m_diffuse, this->data.diffuse);
	s.set_uniform(m_specular, this->data.specular);
	s.set_uniform(m_emission, this->data.emission);
}

void uniform<material>::update_uniform_locations(shader const&sh)
{
	m_shininess = sh.get_location(get_name() + "." + "shininess");
	m_ambient = sh.get_location(get_name() + "." + "ambient");
	m_diffuse = sh.get_location(get_name() + "." + "diffuse");
	m_specular = sh.get_location(get_name() + "." + "specular");
	m_emission = sh.get_location(get_name() + "." + "emission");

	m_update_uniform_locations = false;
}