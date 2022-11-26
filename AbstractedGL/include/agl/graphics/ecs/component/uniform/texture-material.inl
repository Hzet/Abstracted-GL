template <typename TComponent>
uniform<texture_uniform, TComponent>::uniform()
	: uniform_register<texture_uniform, texture>{ "texture" }
{
}

template <typename TComponent>
void uniform<texture_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_ambient = sh.get_location(get_full_name() + "." + "ambient");
		m_diffuse = sh.get_location(get_full_name() + "." + "diffuse");
		m_specular = sh.get_location(get_full_name() + "." + "specular");

		m_update_uniform_locations = false;
	}

	
	auto const& texture = e.get_component<TComponent>();

	auto i = 0;

	if (bindTexture(texture.ambient))
		sh.set_uniform(m_ambient, i++);

	if (bindTexture(texture.diffuse))
		sh.set_uniform(m_diffuse, i++);

	if (bindTexture(texture.specular))
		sh.set_uniform(m_specular, i++);
}

template <typename TComponent>
bool uniform<texture_uniform, TComponent>::bindTexture(const texture_uid &id_texture_2d)
{
	if (!texture_manager::has_texture_2d(id_texture_2d))
		return false;

	texture_manager::get_texture(id_texture_2d).bind();
	return true;
}