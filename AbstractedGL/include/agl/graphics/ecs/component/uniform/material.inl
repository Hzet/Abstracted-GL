template <typename TComponent>
uniform<material_uniform, TComponent>::uniform()
	: uniform_register<material_uniform, material>{ "material" }
{
}

template <typename TComponent>
void uniform<material_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_shininess = sh.get_location(get_full_name() + "." + "shininess");
		m_ambient = sh.get_location(get_full_name() + "." + "ambient");
		m_diffuse = sh.get_location(get_full_name() + "." + "diffuse");
		m_specular = sh.get_location(get_full_name() + "." + "specular");
		//m_emission = sh.get_location(get_full_name() + "." + "emission");

		m_update_uniform_locations = false;
	}
	
	auto const& material = e.get_component<TComponent>();

	sh.set_uniform(m_shininess, material.shininess);
	sh.set_uniform(m_ambient, material.ambient);
	sh.set_uniform(m_diffuse, material.diffuse);
	sh.set_uniform(m_specular, material.specular);
	//s.set_uniform(m_emission, material.emission);
}
