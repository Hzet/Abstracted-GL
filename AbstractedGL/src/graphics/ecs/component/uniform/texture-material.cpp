#include "graphics/ecs/component/uniform/texture-material.hpp"
#include "graphics/texture/texture-atlas.hpp"
#include "core/app/application.hpp"

namespace agl
{
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
		auto& atlas = application::get_resource<texture_atlas>();

		if (!atlas.has_texture_2d(id_texture_2d))
			return false;

		atlas.get_texture(id_texture_2d).bind();
		return true;
	}

	void uniform<texture>::update_uniform_locations(shader const& sh)
	{
		m_ambient = sh.get_location(get_name() + get_index() + "." + "ambient");
		m_diffuse = sh.get_location(get_name() + get_index() + "." + "diffuse");
		m_specular = sh.get_location(get_name() + get_index() + "." + "specular");

		m_update_uniform_locations = false;
	}

}