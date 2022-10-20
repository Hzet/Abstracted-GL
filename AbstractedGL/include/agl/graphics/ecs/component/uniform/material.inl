template <typename TComponent>
uniform<material_uniform, TComponent>::uniform()
	: register_uniform<material>{ "material" }
{
}

template <typename TComponent>
void uniform<material_uniform, TComponent>::send_uniform(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	s.set_uniform(m_shininess, this->data.shininess);
	s.set_uniform(m_ambient, this->data.ambient);
	s.set_uniform(m_diffuse, this->data.diffuse);
	s.set_uniform(m_specular, this->data.specular);
	s.set_uniform(m_emission, this->data.emission);
}

template <typename TComponent>
void uniform<material_uniform, TComponent>::update_uniform_locations(shader const&sh)
{
	m_shininess = sh.get_location(get_name() + get_index() + "." + "shininess");
	m_ambient = sh.get_location(get_name() + get_index() + "." + "ambient");
	m_diffuse = sh.get_location(get_name() + get_index() + "." + "diffuse");
	m_specular = sh.get_location(get_name() + get_index() + "." + "specular");
	m_emission = sh.get_location(get_name() + get_index() + "." + "emission");

	m_update_uniform_locations = false;
}