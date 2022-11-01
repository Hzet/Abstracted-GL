template <typename TComponent>
uniform<texture_uniform, TComponent>::uniform()
	: uniform_register<texture_uniform, texture>{ "texture" }
{
}

template <typename TComponent>
void uniform<texture_uniform, TComponent>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);
	
	auto const& texture = e.get_component<TComponent>();

	auto i = 0;

	if (bindTexture(texture.ambient))
		s.set_uniform(m_ambient, i++);

	if (bindTexture(texture.diffuse))
		s.set_uniform(m_diffuse, i++);

	if (bindTexture(texture.specular))
		s.set_uniform(m_specular, i++);
}

template <typename TComponent>
bool uniform<texture_uniform, TComponent>::bindTexture(const texture_uid &id_texture_2d)
{
	if (!texture_atlas::has_texture_2d(id_texture_2d))
		return false;

	texture_atlas::get_texture(id_texture_2d).bind();
	return true;
}

template <typename TComponent>
void uniform<texture_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_name() + "." + "ambient");
	m_diffuse = sh.get_location(get_name() + "." + "diffuse");
	m_specular = sh.get_location(get_name() + "." + "specular");

	m_update_uniform_locations = false;
}
