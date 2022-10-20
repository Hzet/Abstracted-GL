#include "core/app/application.hpp"
#include "graphics/shader/uniform-base.hpp"
#include "graphics/shader/shader-manager.hpp"
#include "graphics/shader/uniform-group.hpp"
#include "utility/ecs/entity.hpp"

namespace agl
{
	uniform_base::uniform_base(const std::string &name)
		: m_name{ name }
		, m_update_uniform_locations{ true }
	{
	}

	uniform_base::uniform_base(uniform_type_uid id_uniform_type, component_type_uid id_component_type)
		: m_id_component_type_uid(id_component_type)
		, m_id_uniform_type(id_uniform_type)
	{
	}

	std::string uniform_base::get_index() const
	{
		if (m_index < 0)
			return "";

		return "[" + std::to_string(m_index) + "]";
	}

	uniform_type_uid uniform_base::get_type_uid() const
	{
		return m_id_uniform_type;
	}

	component_type_uid uniform_base::get_component_type_uid() const
	{
		return m_id_component_type_uid;
	}

	void uniform_base::set_name(std::string const& name, std::int64_t index)
	{
		m_index= index;
		m_update_uniform_locations = true;
		m_name = name;
	}

	const std::string& uniform_base::get_name() const
	{
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

	void uniform_base::send(shader const& sh, entity const& e)
	{
		static const auto& sh_manager = application::get_resource<shader_manager>();

		const auto &sig = e.get_signature();

		AGL_CORE_ASSERT(!sig[get_component_type_uid()], "component is not attached to this entity");

		const auto &s = sh_manager.get_shader(get_shader_uid());
		s.set_active();

		this->send_uniform(s, e);
	}
}