#include "graphics/shader/shader-program.hpp"
#include "system/debug/error.hpp"
#include "system/glcore/gl-core.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace agl
{
	constexpr static std::uint64_t get_bit(shader_type type)
	{
		switch (type)
		{
			case SHADER_VERTEX: return GL_VERTEX_SHADER_BIT;
			case SHADER_TESS_CONTROL: return GL_TESS_CONTROL_SHADER_BIT;
			case SHADER_TESS_EVALUATION: return GL_TESS_EVALUATION_SHADER_BIT;
			case SHADER_GEOMETRY: return GL_GEOMETRY_SHADER_BIT;
			case SHADER_FRAGMENT: return GL_FRAGMENT_SHADER_BIT;
			case SHADER_COMPUTE: return GL_COMPUTE_SHADER_BIT;
		}

		AGL_CORE_WARNING("Invalid s type - {}", type);
		return 0u;
	}

	void shader::load_from_file(const std::string &vertex, const std::string &fragment, const std::string &geometry /*= ""*/, const std::string &tessControl /*= ""*/, const std::string &tessEvaluation /*= ""*/, const std::string &compute /*= ""*/)
	{
		attach_from_file(SHADER_VERTEX, vertex);
		attach_from_file(SHADER_FRAGMENT, fragment);
		attach_from_file(SHADER_GEOMETRY, geometry);
		attach_from_file(SHADER_TESS_CONTROL, tessControl);
		attach_from_file(SHADER_TESS_EVALUATION, tessEvaluation);
		attach_from_file(SHADER_COMPUTE, compute);
	}

	void shader::load_from_source(const std::string &vertex, const std::string &fragment, const std::string &geometry /*= ""*/, const std::string &tessControl /*= ""*/, const std::string &tessEvaluation /*= ""*/, const std::string &compute /*= ""*/)
	{
		attach_from_source(SHADER_VERTEX, vertex);
		attach_from_source(SHADER_FRAGMENT, fragment);
		attach_from_source(SHADER_GEOMETRY, geometry);
		attach_from_source(SHADER_TESS_CONTROL, tessControl);
		attach_from_source(SHADER_TESS_EVALUATION, tessEvaluation);
		attach_from_source(SHADER_COMPUTE, compute);
	}

	shader::shader()
		: m_id_object(0u)
		, m_shader_bits(0u)
	{
	}

	shader::~shader()
	{
		if (!is_move_constructing())
			destroy();
	}

	bool shader::attach_from_source(shader_type type, const std::string &source)
	{
		if (source.empty())
			return false;

		m_sub_shaders.emplace_back(sub_shader());
		if (m_sub_shaders.back().set_source(type, source))
		{
			set_bit(get_bit(type));
			return true;
		}

		return false;
	}

	bool shader::attach_from_file(shader_type type, const std::string &filename)
	{
		if (filename.empty())
			return false;

		m_sub_shaders.emplace_back(sub_shader());
		const auto result = m_sub_shaders.back().load_from_file(type, filename);

		if (result)
			set_bit(get_bit(type));

		return result;
	}

	bool shader::attach_from_memory(shader_type type, const char *data, std::uint64_t size)
	{
		m_sub_shaders.emplace_back(sub_shader());
		const auto result = m_sub_shaders.back().load_from_memory(type, data, size);

		if (result)
			set_bit(get_bit(type));

		return result;
	}

	bool shader::link()
	{
		if (!compile_sub_shaders())
			return false;

		create();

		for (const auto &v : m_sub_shaders)
			AGL_CALL(glAttachShader(m_id_object, v.get_id()));

		AGL_CALL(glLinkProgram(m_id_object));

		auto result = std::int32_t{};
		AGL_CALL(glGetProgramiv(m_id_object, GL_LINK_STATUS, &result));

		m_sub_shaders.clear();

		if (!result)
		{
			auto length = std::int32_t{};
			AGL_CALL(glGetProgramiv(m_id_object, GL_INFO_LOG_LENGTH, &length));

			auto message = std::string{};
			message.resize(length);

			AGL_CALL(glGetProgramInfoLog(m_id_object, length, NULL, &message[0u]));
			AGL_CORE_WARNING("Failed to link a s program! \nDescription: {}", message);

			return false;
		}

		return true;
	}

	void shader::set_active() const
	{
		bind();
	}

	bool shader::is_created() const
	{
		return m_id_object != 0u;
	}

	bool shader::has_shader(std::uint64_t bit) const
	{
		return (m_shader_bits & bit);
	}

	shader_uid shader::get_shader_uid() const
	{
		return m_id_shader;
	}

	void shader::create()
	{
		if (is_created())
			destroy();

		AGL_CALL(m_id_object = glCreateProgram());
	}

	void shader::bind() const
	{
		AGL_CALL(glUseProgram(m_id_object));
	}

	void shader::set_bit(std::uint64_t bit)
	{
		m_shader_bits |= bit;
	}

	void shader::destroy()
	{
		AGL_CALL(glDeleteProgram(m_id_object));

		m_id_object = 0u;
		m_shader_bits = 0u;
	}

	bool shader::compile_sub_shaders()
	{
		auto result = true;
		for (auto &v : m_sub_shaders)
		{
			if (!v.compile())
			{
				result = false;
				break;
			}
		}

		if (!result)
			m_sub_shaders.clear();

		return result;
	}

	void shader::set_uniform(std::int32_t location, const float value) const
	{
		glUniform1f(location, value);
	}

	void shader::set_uniform(std::int32_t location, const std::int32_t value) const
	{
		AGL_CALL(glUniform1i(location, value));
	}

	void shader::set_uniform(std::int32_t location, const std::uint32_t value) const
	{
		AGL_CALL(glUniform1ui(location, value));
	}

	void shader::set_uniform(std::int32_t location, const glm::vec2 &value) const
	{
		AGL_CALL(glUniform2f(location, value.x, value.y));
	}

	void shader::set_uniform(std::int32_t location, const glm::vec3 &value) const
	{
		AGL_CALL(glUniform3f(location, value.x, value.y, value.z));
	}

	void shader::set_uniform(std::int32_t location, const glm::vec4 &value) const
	{
		AGL_CALL(glUniform4f(location, value.x, value.y, value.z, value.w));
	}

	void shader::set_uniform(std::int32_t location, const glm::mat4 &value) const
	{
		AGL_CALL(glUniformMatrix4fv(location, 1u, GL_FALSE, glm::value_ptr(value)));
	}

	void shader::set_uniform(std::int32_t location, std::int32_t const * const value, std::uint64_t count) const
	{
		AGL_CALL(glUniform1iv(location, count, value));
	}

	void shader::set_uid(shader_uid id_shader)
	{
		m_id_shader = id_shader;
	}

	std::int32_t shader::get_location(const std::string &name) const
	{
		auto result = std::int32_t{};

		AGL_CALL(result = glGetUniformLocation(m_id_object, name.c_str()));
		AGL_CORE_ASSERT(result != -1, "Uniform with such name does not exist!\nName: {}", name);

		return result;
	}
}

