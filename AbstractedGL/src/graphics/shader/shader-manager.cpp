#include "agl/graphics/shader/shader-manager.hpp"
#include "agl/system/debug/assert.hpp"

namespace agl
{
	std::uint64_t shader_manager::get_index(const shader_uid &id_shader)
	{
		return id_shader - 1ul;
	}


	shader_uid shader_manager::load_from_file(const std::string &vertex, const std::string &fragment, const std::string &geometry, const std::string &tessControl, const std::string &tessEvaluation, const std::string &compute)
	{
		auto sh = shader{};

		sh.load_from_file(vertex, fragment, geometry, tessControl, tessEvaluation, compute);

		return add_shader(std::move(sh));
	}

	shader_uid const& shader_manager::get_shader_uid(std::uint64_t index) const
	{
		return m_shaders[index].get_shader_uid();
	}

	void shader_manager::set_active_shader(shader_uid id_shader)
	{
		if (m_active_shader == id_shader)
			return;

		m_active_shader = id_shader;
		get_shader(id_shader).set_active();
	}

	shader const& shader_manager::get_active_shader() const
	{
		return get_shader(m_active_shader);
	}

	const shader& shader_manager::get_shader(shader_uid id_shader) const
	{
		return m_shaders[get_index(id_shader)];
	}

	shader_uid shader_manager::add_shader(shader &&s)
	{
		m_shaders.resize(m_shaders.size() + 1);

		s.set_uid(shader_uid::create());

		auto index = get_index(s.get_shader_uid());

		m_shaders[index] = std::move(s);
		return m_shaders[index].get_shader_uid();
	}

	void shader_manager::link_all_shaders()
	{
		for (auto &v : m_shaders)
			v.link();
	}
}