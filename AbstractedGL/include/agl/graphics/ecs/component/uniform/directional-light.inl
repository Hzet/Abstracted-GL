template <typename TComponent>
uniform<directional_light_uniform, TComponent>::uniform()
	: uniform_register<directional_light_uniform, directional_light>{ "directional_light" }
{
}

template <typename TComponent>
void uniform<directional_light_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);

	auto const& light = e.get_component<TComponent>();

	s.set_uniform(m_ambient, light.ambient);
	s.set_uniform(m_color, light.color);
	s.set_uniform(m_diffuse, light.diffuse);
	s.set_uniform(m_specular, light.specular);
}

template <typename TComponent>
void uniform<directional_light_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_full_name() + "." + "ambient");
	m_color = sh.get_location(get_full_name() + "." + "color");
	m_diffuse = sh.get_location(get_full_name() + "." + "diffuse");
	m_specular = sh.get_location(get_full_name() + "." + "specular");

	update_uniform_locations = false;
}
