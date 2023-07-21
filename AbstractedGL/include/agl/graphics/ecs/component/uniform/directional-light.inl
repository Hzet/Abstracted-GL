template <typename TComponent>
uniform<directional_light_uniform, TComponent>::uniform()
	: uniform_register<directional_light_uniform, directional_light>{ "directional_light" }
{
}

template <typename TComponent>
void uniform<directional_light_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_ambient = sh.get_location(get_indexed_name() + "." + "ambient");
		m_color = sh.get_location(get_indexed_name() + "." + "color");
		m_diffuse = sh.get_location(get_indexed_name() + "." + "diffuse");
		m_specular = sh.get_location(get_indexed_name() + "." + "specular");

		m_update_uniform_locations = false;
	}


	auto const& light = e.get_component<TComponent>();

	sh.set_uniform(m_ambient, light.ambient);
	sh.set_uniform(m_color, light.color);
	sh.set_uniform(m_diffuse, light.diffuse);
	sh.set_uniform(m_specular, light.specular);
}
