template <typename TComponent>
uniform<texture_uniform, TComponent>::uniform()
	: uniform_register<texture_uniform, texture>{ "texture_material" }
{
}

template <typename TComponent>
void uniform<texture_uniform, TComponent>::send(const shader &sh, const entity &e)
{
	if (m_update_uniform_locations)
	{
		m_ambient = sh.get_location(get_full_name() + "." + "ambient");
		//m_ambient_active = sh.get_location(get_full_name() + "." + "ambient_active");
		//m_diffuse = sh.get_location(get_full_name() + "." + "diffuse");
		//m_specular = sh.get_location(get_full_name() + "." + "specular");

		m_update_uniform_locations = false;
	}

	static auto& texture_manager = application::get_resource<agl::texture_manager>();

	auto const& texture = e.get_component<TComponent>();

	auto i = 0;

	//sh.set_uniform(m_ambient_active, texture.ambient != texture_uid::INVALID);
	if (texture.ambient != texture_uid::INVALID)
	{
		texture_manager.bind_texture(texture.ambient);
		sh.set_uniform(m_ambient, i++);
	}

	//
	//if (bindTexture(texture.diffuse))
	//	sh.set_uniform(m_diffuse, i++);
	//
	//if (bindTexture(texture.specular))
	//	sh.set_uniform(m_specular, i++);
}
