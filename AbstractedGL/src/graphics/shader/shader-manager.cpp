#include "graphics/shader/shader-manager.hpp"
#include "system/debug/assert.hpp"

namespace agl
{
	std::uint64_t shader_manager::get_index(const shader_uid &id_shader)
	{
		return id_shader - 1ul;
	}


	void shader_manager::load_from_file(const std::string &vertex, const std::string &fragment, const std::string &geometry, const std::string &tessControl, const std::string &tessEvaluation, const std::string &compute)
	{
		auto sh = shader{};

		sh.load_from_file(vertex, fragment, geometry, tessControl, tessEvaluation, compute);

		sh.set_uid(shader_uid::create());

		add_shader(sh.get_shader_uid(), std::move(sh));
	}

	shader_uid shader_manager::get_shader_uid(std::uint64_t index) const
	{
		return m_shaders[index].get_shader_uid();
	}

	const shader& shader_manager::get_shader(shader_uid id_shader) const
	{
		return m_shaders[get_index(id_shader)];
	}

	void shader_manager::add_shader(shader_uid id_shader, shader &&s)
	{
		if (get_index(id_shader) >= m_shaders.size())
			m_shaders.resize(id_shader);

		m_shaders[get_index(id_shader)] = std::move(s);
	}

	void shader_manager::link_all_shaders()
	{
		for (auto &v : m_shaders)
			v.link();
	}
}