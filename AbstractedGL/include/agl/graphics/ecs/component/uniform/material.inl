template <typename TComponent>
uniform<material_uniform, TComponent>::uniform()
	: uniform_register<material_uniform, material>{ "material" }
{
}

template <typename TComponent>
void uniform<material_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);
	
	auto const& material = e.get_component<TComponent>();

	s.set_uniform(m_shininess, material.shininess);
	s.set_uniform(m_ambient, material.ambient);
	s.set_uniform(m_diffuse, material.diffuse);
	s.set_uniform(m_specular, material.specular);
	//s.set_uniform(m_emission, material.emission);
}

template <typename TComponent>
void uniform<material_uniform, TComponent>::update_uniform_locations(shader const&sh)
{
	m_shininess = sh.get_location(get_full_name() + "." + "shininess");
	m_ambient = sh.get_location(get_full_name() + "." + "ambient");
	m_diffuse = sh.get_location(get_full_name() + "." + "diffuse");
	m_specular = sh.get_location(get_full_name() + "." + "specular");
	//m_emission = sh.get_location(get_full_name() + "." + "emission");

	m_update_uniform_locations = false;
}