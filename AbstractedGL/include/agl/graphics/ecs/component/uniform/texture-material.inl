template <typename TComponent>
uniform<texture_material_uniform, TComponent>::uniform()
	: register_uniform<texture_material>{ "texture" }
{
}

template <typename TComponent>
void uniform<texture_material_uniform, TComponent>::send_uniform(const shader &s, const entity &e)
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

template <typename TComponent>
bool uniform<texture_material_uniform, TComponent>::bindTexture(const texture_uid &id_texture_2d)
{
	auto& atlas = application::get_resource<texture_atlas>();

	if (!atlas.has_texture_2d(id_texture_2d))
		return false;

	atlas.get_texture(id_texture_2d).bind();
	return true;
}

template <typename TComponent>
void uniform<texture_material_uniform, TComponent>::update_uniform_locations(shader const& sh)
{
	m_ambient = sh.get_location(get_name() + get_index() + "." + "ambient");
	m_diffuse = sh.get_location(get_name() + get_index() + "." + "diffuse");
	m_specular = sh.get_location(get_name() + get_index() + "." + "specular");

	m_update_uniform_locations = false;
}