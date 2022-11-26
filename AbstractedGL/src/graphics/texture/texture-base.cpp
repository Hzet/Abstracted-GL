#include "agl/graphics/texture/texture-base.hpp"
#include "agl/system/glcore/gl-core.hpp"

namespace agl
{
	texture_base::~texture_base()
	{
		if (is_move_constructing())
			destroy();
	}

	void texture_base::set_parameter(const std::uint64_t setting, const std::uint64_t value) const
	{
		AGL_CORE_ASSERT(is_created(), "Can not set a parameter on non existing texture!");

		bind();
		AGL_CALL(glTexParameteri(get_type(), setting, value));
	}

	bool texture_base::is_created() const
	{
		return m_id_object != 0;
	}

	texture_type texture_base::get_type() const
	{
		return m_type;
	}

	std::string const& texture_base::get_filepath() const
	{
		return m_filepath;
	}

	glm::vec3 texture_base::get_size() const
	{
		return m_size;
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

}