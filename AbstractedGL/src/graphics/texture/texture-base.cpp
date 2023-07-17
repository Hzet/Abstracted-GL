#include "agl/graphics/texture/texture-base.hpp"
#include "agl/system/glcore/gl-core.hpp"

namespace agl
{
	texture_base::~texture_base()
	{
		if (is_move_constructing())
			destroy();
	}

	bool texture_base::is_created() const
	{
		return m_id_object != 0;
	}

	texture_type texture_base::get_type() const
	{
		return m_type;
	}

	void texture_base::set_texture_wrap(texture_wrap_type s, texture_wrap_type t, texture_wrap_type r)
	{
		m_parameters.wrap = { s, t, r };
	}

	void texture_base::set_size_filters(texture_pixel_match min, texture_pixel_match mag)
	{
		m_parameters.filters = { min, mag };
	}

	void texture_base::set_mipmap_levels(std::uint64_t min, std::uint64_t max)
	{
		m_parameters.mipmap = { min, max };
	}

	texture_parameters const&  texture_base::get_parameters() const
	{
		return m_parameters;
	}

	void texture_base::enable_mipmaps(bool status)
	{
		m_parameters.create_mipmaps = status;
	}

	std::string const& texture_base::get_filepath() const
	{
		return m_filepath;
	}

	glm::vec3 texture_base::get_size() const
	{
		return m_size;
	}

	agl::texture_format_type texture_base::get_format_type() const
	{
		return m_format;
	}

	void texture_base::set_format_type(texture_format_type format_type)
	{
		m_format = format_type;
	}

	texture_base::texture_base(texture_type type)
		: m_type{ type }
	{
	}

	void texture_base::create()
	{
		AGL_CALL(glGenTextures(1u, &m_id_object));
	}

	void texture_base::destroy()
	{
		if (!is_created())
			return;

		AGL_CALL(glDeleteTextures(1u, &m_id_object));

		m_id_object = 0u;
	}

	void texture_base::bind() const
	{
		AGL_CALL(glBindTexture(get_type(), m_id_object));
	}

	void texture_base::unbind() const
	{
		AGL_CALL(glBindTexture(get_type(), 0u));
	}


	void texture_base::set_parameters() const
	{
		if (!is_created())
			return;

		bind();

		// wrap
		if(m_parameters.wrap.s != TEXTURE_WRAP_NONE)
			AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_WRAP_S, m_parameters.wrap.s));

		if(m_parameters.wrap.t != TEXTURE_WRAP_NONE)
			AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_WRAP_T, m_parameters.wrap.t));

		if(m_parameters.wrap.r != TEXTURE_WRAP_NONE)
			AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_WRAP_R, m_parameters.wrap.r));

		// filter
		if(m_parameters.filters.minification != TEXTURE_PIXEL_NONE)
			AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_MIN_FILTER, m_parameters.filters.minification));

		if (m_parameters.filters.magnification != TEXTURE_PIXEL_NONE)
			AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_MAG_FILTER, m_parameters.filters.magnification));

		AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_BASE_LEVEL, m_parameters.mipmap.min));
		AGL_CALL(glTexParameteri(get_type(), GL_TEXTURE_MAX_LEVEL, m_parameters.mipmap.max));
	}
}