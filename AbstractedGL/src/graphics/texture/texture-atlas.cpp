#include "graphics/texture/texture-atlas.hpp"
#include "system/debug/error.hpp"

namespace agl
{
	texture_uid texture_atlas::add_texture_2d(texture_2d texture, const std::string &identifier)
	{
		if (has_texture_2d(identifier))
			return get_texture_uid(identifier);

		auto result = texture_uid{};
		m_textures_2d.emplace(result, texture);
		m_directory_map_2d.emplace(identifier, result);

		return result;
	}

	bool texture_atlas::has_texture_2d(const std::string &filepath)
	{
		return m_directory_map_2d.find(filepath) != m_directory_map_2d.end();
	}

	bool texture_atlas::has_texture_2d(const texture_uid &id_texture_2d)
	{
		return m_textures_2d.find(id_texture_2d) != m_textures_2d.end();
	}

	texture_uid texture_atlas::load_from_file(std::string const& filepath)
	{
		if (has_texture_2d(filepath))
			return get_texture_uid(filepath);

		auto result = texture_2d{};

		if (!result.load_from_file(filepath))
		{
			AGL_CORE_WARNING("Failed to load texture! {}", filepath);
			return texture_uid::INVALID;
		}

		return add_texture_2d(result, filepath);
	}

	texture_base& texture_atlas::get_texture(const texture_uid &id_texture_2d)
	{
		return get_texture_2d(id_texture_2d);
	}

	texture_uid texture_atlas::get_texture_uid(const std::string &filepath)
	{
		AGL_CORE_ASSERT(m_directory_map_2d.find(filepath) != m_directory_map_2d.end(), "Index out of bounds!");

		return m_directory_map_2d.find(filepath)->second;
	}

	texture_2d& texture_atlas::get_texture_2d(const texture_uid &id_texture_2d)
	{
		AGL_CORE_ASSERT(m_textures_2d.find(id_texture_2d) != m_textures_2d.end(), "Index out of bounds!");

		return m_textures_2d.find(id_texture_2d)->second;
	}

	texture_2d& texture_atlas::get_texture_2d(const std::string &filepath)
	{
		AGL_CORE_ASSERT(m_directory_map_2d.find(filepath) != m_directory_map_2d.end(), "Index out of bounds!");

		return get_texture_2d(m_directory_map_2d.find(filepath)->second);
	}
}