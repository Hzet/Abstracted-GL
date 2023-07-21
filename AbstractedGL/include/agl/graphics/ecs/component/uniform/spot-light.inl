template <typename TComponent>
uniform<spot_light_uniform, TComponent>::uniform()
	: uniform_register<spot_light_uniform, spot_light>{ "spot_light" }
{
}

template <typename TComponent>
void uniform<spot_light_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_ambient = sh.get_location(get_indexed_name() + "." + "ambient");
		m_color = sh.get_location(get_indexed_name() + "." + "color");
		m_cut_off = sh.get_location(get_indexed_name() + "." + "cut_off");
		m_diffuse = sh.get_location(get_indexed_name() + "." + "diffuse");
		m_range = sh.get_location(get_indexed_name() + "." + "range");
		m_specular = sh.get_location(get_indexed_name() + "." + "specular");

		m_update_uniform_locations = false;
	}

	auto const& light = e.get_component<TComponent>();

	sh.set_uniform(m_ambient, light.ambient);
	sh.set_uniform(m_color, light.color);
	sh.set_uniform(m_cut_off, light.cut_off);
	sh.set_uniform(m_diffuse, light.diffuse);
	sh.set_uniform(m_range, light.range);
	sh.set_uniform(m_specular, light.specular);
}
