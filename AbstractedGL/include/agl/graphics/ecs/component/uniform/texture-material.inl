uniform<texture>::uniform()
	: register_uniform<texture>{ "texture" }
{
}

void uniform<texture>::send(const shader &s, const entity &e)
{
	if (m_update_uniform_locations)
		update_uniform_locations(s);
	
	auto i = 0;

	if (bindTexture(this->data.ambient))
		s.set_uniform(m_ambient, i++);

	if (bindTexture(this->data.diffuse))
		s.set_uniform(m_diffuse, i++);

	if (bindTexture(this->data.specular))
		s.set_uniform(m_specular, i++);
}

bool uniform<texture>::bindTexture(const texture_uid &id_texture_2d)
{
	if (!texture_atlas::has_texture_2d(id_texture_2d))
		return false;

	texture_atlas::get_texture(id_texture_2d).bind();
	return true;
}

void uniform<texture>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_name() + "." + "ambient");
	m_diffuse = sh.get_location(get_name() + "." + "diffuse");
	m_specular = sh.get_location(get_name() + "." + "specular");

	m_update_uniform_locations = false;
}
