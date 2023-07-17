#pragma once
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

#include "agl/graphics/texture/texture-type.hpp"
#include "agl/graphics/texture/texture-wrap-type.hpp"
#include "agl/graphics/texture/texture-pixel-match-type.hpp"
#include "agl/graphics/texture/texture-format-type.hpp"
#include "agl/graphics/texture/texture-uid.hpp"
#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	struct texture_parameters
	{
		struct size_filters
		{
			texture_pixel_match minification;
			texture_pixel_match magnification;
		};

		struct wrapping_type
		{
			texture_wrap_type s;
			texture_wrap_type t;
			texture_wrap_type r;
		};

		struct mipmap_levels
		{
			std::uint64_t min = 0;
			std::uint64_t max = 1000;
		};

		bool create_mipmaps = false;
		wrapping_type wrap;
		size_filters filters;
		mipmap_levels mipmap;
	};

	/// <summary>
	/// The base class for texture providing gl_object implementation
	/// and general texture specific methods.
	/// </summary>
	class texture_base
		: public destructive_move
	{
	public:
		texture_base() = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~texture_base();

		/// <summary>
		/// Bind OpenGL object.
		/// </summary>
		void bind() const;

		/// <summary>
		/// Unbind OpenGL object.
		/// </summary>
		void unbind() const;

		bool is_created() const;

		std::string const& get_filepath() const;

		glm::vec3 get_size() const;

		texture_format_type get_format_type() const;
		void set_format_type(texture_format_type format_type);

		/// <summary>
		/// Pure virtual method to get the texture's target.
		/// </summary>
		/// <returns>
		/// OpenGL texture target enum
		/// </returns>
		texture_type get_type() const;

		texture_parameters const& get_parameters() const;

		void enable_mipmaps(bool status);
		void set_mipmap_levels(std::uint64_t min, std::uint64_t max);
		void set_size_filters(texture_pixel_match minification, texture_pixel_match magnification);
		void set_texture_wrap(texture_wrap_type s, texture_wrap_type t, texture_wrap_type r);

	protected:
		texture_base(texture_type type);

		/// <summary>
		/// uniform_register OpenGL object.
		/// </summary>
		void create();

		/// <summary>
		/// Unregister the OpenGL object and clear resources.
		/// </summary>
		void destroy();
		void set_parameters() const;

	protected:
		std::string m_filepath;
		glm::vec3 m_size;
		texture_type m_type;

	private:
		std::uint32_t m_id_object;
		texture_uid m_id_texture;
		texture_format_type m_format;
		texture_parameters m_parameters;

	private:
		friend class texture_manager;
	};
}