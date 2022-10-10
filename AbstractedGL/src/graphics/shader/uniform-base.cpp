#include "graphics/shader/uniform-base.hpp"

namespace agl
{
	uniform_base::uniform_base(const std::string &name)
	{
		set_name(name);
	}

	uniform_base::uniform_base(uniform_data_type_uid id_uniform_data_type, component_type_uid id_component_type)
		: m_id_component_type_uid(id_component_type)
		, m_id_uniform_data_type(id_uniform_data_type)
	{
	}

	uniform_data_type_uid uniform_base::get_data_type_uid() const
	{
		return m_id_uniform_data_type;
	}

	component_type_uid uniform_base::get_component_type_uid() const
	{
		return m_id_component_type_uid;
	}

	void uniform_base::set_name(const std::string &name)
	{
		m_name = name + ".";
	}

	const std::string& uniform_base::get_name() const
	{
		return m_name;
	}

	void uniform_base::add_shader_uid(shader_uid id_shader)
	{
		if (!has_shader_uid(id_shader))
			m_id_shader.push_back(id_shader);
	}

	const std::vector<shader_uid>& uniform_base::get_shader_uids() const
	{
		return m_id_shader;
	}

	bool uniform_base::has_shader_uid(shader_uid id_shader) const
	{
		for (auto &v : m_id_shader)
			if (v == id_shader)
				return true;
		return false;
	}

	void uniform_base::remove_shader_uid(shader_uid id_shader)
	{
		for (auto it = m_id_shader.cbegin(); it != m_id_shader.cend(); ++it)
			if (*it == id_shader)
			{
				m_id_shader.erase(it);
				break;
			}
	}
}