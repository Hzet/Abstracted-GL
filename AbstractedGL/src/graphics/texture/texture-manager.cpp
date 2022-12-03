#include "agl/graphics/texture/texture-manager.hpp"
#include "agl/system/debug/error.hpp"
#include "agl/system/glcore/gl-core.hpp"

namespace agl
{
	texture_uid texture_manager::add_texture_2d(texture_2d texture)
	{
		if (has_texture_2d(texture.get_filepath()))
			return get_texture_uid(texture.get_filepath());

		auto const result = texture_uid::create();

		texture.m_id_texture = result;
		m_textures_2d.push_back(texture);
		m_directory_map_2d.emplace(texture.get_filepath(), result);

		return result;
	}

	bool texture_manager::has_texture_2d(const std::string &filepath)
	{
		return m_directory_map_2d.find(filepath) != m_directory_map_2d.cend();
	}

	bool texture_manager::has_texture_2d(const texture_uid &id_texture_2d)
	{
		return m_textures_2d.size() >= id_texture_2d;
	}

	void texture_manager::bind_texture(texture_uid const& id_texture)
	{
		for (auto const& id : m_bound_textures)
			if (id == id_texture)
				return;

		m_bound_textures.push_back(id_texture);

		auto const& texture = m_textures_2d[id_texture - 1];

		//AGL_CALL(glActiveTexture(GL_TEXTURE0 + m_bound_textures.get_count() - 1));
		texture.bind();
	}

	void texture_manager::unbind_textures()
	{
		for (auto& id_texture : m_bound_textures)
			m_textures_2d[id_texture - 1].unbind();

		m_bound_textures.clear();
	}

	texture_uid texture_manager::load_from_file(std::string const& filepath)
	{
		if (has_texture_2d(filepath))
			return get_texture_uid(filepath);

		auto texture = texture_2d{};

		texture.enable_mipmaps(true);
		texture.set_size_filters(TEXTURE_PIXEL_LINEAR_MIPMAP_LINEAR, TEXTURE_PIXEL_LINEAR);
		texture.set_texture_wrap(TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_NONE);

		if (!texture.load_from_file(filepath))
		{
			AGL_CORE_WARNING("Failed to load texture! {}", filepath);
			return texture_uid{};
		}

		return add_texture_2d(texture);
	}

	texture_base& texture_manager::get_texture(const texture_uid &id_texture_2d)
	{
		return get_texture_2d(id_texture_2d);
	}

	texture_uid texture_manager::get_texture_uid(const std::string &filepath)
	{
		AGL_CORE_ASSERT(m_directory_map_2d.find(filepath) != m_directory_map_2d.cend(), "Index out of bounds!");

		return m_directory_map_2d.find(filepath)->second;
	}

	texture_2d& texture_manager::get_texture_2d(const texture_uid &id_texture_2d)
	{
		AGL_CORE_ASSERT(has_texture_2d(id_texture_2d), "Index out of bounds!");

		return m_textures_2d[id_texture_2d];
	}

	texture_2d& texture_manager::get_texture_2d(const std::string &filepath)
	{
		AGL_CORE_ASSERT(m_directory_map_2d.find(filepath) != m_directory_map_2d.cend(), "Index out of bounds!");

		return get_texture_2d(m_directory_map_2d.find(filepath)->second);
	}
}