#include "agl/graphics/shader/uniform-base.hpp"

namespace agl
{
	uniform_base::uniform_base(const std::string &name)
		: m_index{ -1 }
		, m_name{ name }
		, m_update_uniform_locations{ true }
	{
	}

	uniform_base::uniform_base(uniform_type_uid id_uniform_type, component_type_uid id_component_type)
		: m_index{ -1 }
		, m_id_component_type_uid(id_component_type)
		, m_id_uniform_type(id_uniform_type)
		, m_update_uniform_locations{ true }
	{
	}

	uniform_type_uid uniform_base::get_uniform_type_uid() const
	{
		return m_id_uniform_type;
	}

	component_type_uid uniform_base::get_component_type_uid() const
	{
		return m_id_component_type_uid;
	}

	bool uniform_base::is_indexed() const
	{
		return m_index != -1;
	}

	void uniform_base::set_name(std::string const& name, std::int64_t index)
	{
		m_update_uniform_locations = true;

		m_index = index;
		m_name = name;
	}

	const std::string& uniform_base::get_name() const
	{
		return m_name;
	}

	std::string uniform_base::get_indexed_name()
	{
		if (is_indexed())
			return m_name + "[" + std::to_string(m_index) + "]";
		
		return m_name;
	}

	void uniform_base::set_shader_uid(shader_uid id_shader)
	{
		m_update_uniform_locations = true;

		m_id_shader = id_shader;
	}

	shader_uid uniform_base::get_shader_uid() const
	{
		return m_id_shader;
	}
}