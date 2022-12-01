#pragma once
#include <unordered_map>

#include "agl/core/app/resource.hpp"
#include "agl/graphics/texture/texture2d.hpp"


namespace agl
{
	/// <summary>
	/// A static / global container that stores textures.
	/// </summary>
	class texture_manager
		: public resource_base
	{
	public:
		void bind_texture(texture_uid const& id_texture);

		void unbind_textures();

		texture_uid	load_from_file(std::string const& filepath);

		/// <summary>
		/// Returns any texture that 'id_texture_2d' is assigned to.
		/// </summary>
		/// <param name="id_texture_2d"></param>
		/// <returns></returns>
		texture_base& get_texture(const texture_uid &id_texture_2d);

		/// <summary>
		/// Returns the unique identifier of a texture loaded from 'filepath'.
		/// </summary>
		/// <param name="filepath">The texture's filepath</param>
		/// <returns>The texture's unique identifier</returns>
		texture_uid get_texture_uid(const std::string &filepath);

		/// <summary>
		/// Adds a 2D 'texture' to the container that will be identified with a 'identifier'
		/// and returns an unique identifier that has been assigned to this occurrance.
		/// </summary>
		/// <param name="texture">The texture</param>
		/// <param name="identifier">The identifier</param>
		/// <returns>The unique identifier</returns>
		texture_uid add_texture_2d(texture_2d texture);

		/// <summary>
		/// Returns a 2D texture that 'filepath' is assigned to.
		/// </summary>
		/// <param name="filepath">The texture's filepath</param>
		/// <returns>The 2D texture</returns>
		texture_2d& get_texture_2d(const std::string &filepath);

		/// <summary>
		/// Returns a 2D texture that 'id_texture_2d' is assigned to.
		/// </summary>
		/// <param name="id_texture_2d">The texture's unique identifier</param>
		/// <returns>The 2D texture</returns>
		texture_2d& get_texture_2d(const texture_uid &id_texture_2d);

		/// <summary>
		/// Checks whether the 2D texture from 'filepath' is present in the atlas.
		/// </summary>
		/// <param name="filepath">The texture's filepath</param>
		/// <returns>
		/// true - atlas contains the texture
		/// false - atlas does not contain the texture
		/// </returns>
		bool has_texture_2d(const std::string &filepath);

		/// <summary>
		/// Checks whether the 2D texture identified with 'id_texture_2d' is present in the atlas.
		/// </summary>
		/// <param name="id_texture_2d">The texture's unique identifier</param>
		/// <returns>
		/// true - atlas contains the texture
		/// false - atlas does not contain the texture
		/// </returns>
		bool has_texture_2d(const texture_uid &id_texture_2d);

	private:
		virtual void dummy() const override {}

	private:
		std::vector<texture_uid> m_bound_textures;
		std::unordered_map<std::string, texture_uid> m_directory_map_2d;
		std::vector<texture_2d> m_textures_2d;
	};
}