#include "graphics/shader/shader-sub-program.hpp"
#include "system/glcore/gl-core.hpp"
#include "system/debug/error.hpp"

#include <fstream>

namespace agl
{
	static const char* get_shader_name(shader_type type)
	{
		switch (type)
		{
		case SHADER_VERTEX: return "Vertex";
		case SHADER_TESS_CONTROL: return "Tessellation control";
		case SHADER_TESS_EVALUATION: return "Tessellation evaluation";
		case SHADER_GEOMETRY: return "Geometry";
		case SHADER_FRAGMENT: return "Fragment";
		case SHADER_COMPUTE: return "Compute";
		}

		return "invalid";
	}

	sub_shader::sub_shader()
		: m_id_object(0u)
		, m_type(SHADER_INVALID)
	{
	}

	sub_shader::~sub_shader()
	{
		if (!is_move_constructing())
			destroy();
	}

	bool sub_shader::is_created() const
	{
		return m_id_object != 0u;
	}

	std::uint32_t sub_shader::get_id() const
	{
		return m_id_object;
	}

	shader_type sub_shader::get_type() const
	{
		return m_type;
	}

	bool sub_shader::load_from_file(shader_type type, const std::string &filename)
	{
		auto file = std::ifstream{ filename, std::ios::in | std::ios::beg };

		if (!file.is_open())
		{
			AGL_CORE_EXCEPTION(ExFileOpen, "\nFilename: {}", filename);
			return false;
		}

		m_source = "";
		auto line = std::string{};

		while (std::getline(file, line))
			m_source += line + '\n';

		file.close();

		m_type = type;

		return true;
	}

	bool sub_shader::load_from_memory(shader_type type, const char *source, std::uint64_t size)
	{
		if (source == nullptr)
			return false;

		m_source.resize(size);
		for (auto i = 0u; i < size; i++)
			m_source[i] = *(source + i);

		m_source += '\0';

		m_type = type;

		return true;
	}

	bool sub_shader::set_source(shader_type type, const std::string &source)
	{
		if (source.empty())
			return false;

		m_source = source;
		m_type = type;

		return true;
	}

	bool sub_shader::compile()
	{
		if (m_source.empty())
		{
			AGL_CORE_WARNING("Shader [{}] source code has not been loaded!", get_shader_name(m_type));
			return false;
		}

		const char *source = m_source.c_str();

		create();
		AGL_CALL(glShaderSource(m_id_object, 1u, &source, NULL));
		AGL_CALL(glCompileShader(m_id_object));

		auto result = std::int32_t{};

		AGL_CALL(glGetShaderiv(m_id_object, GL_COMPILE_STATUS, &result));

		if (!result)
		{
			auto length = std::int32_t{};
			auto message = std::string{};
			AGL_CALL(glGetShaderiv(m_id_object, GL_INFO_LOG_LENGTH, &length));

			message.resize(length);
			AGL_CALL(glGetShaderInfoLog(m_id_object, length, nullptr, &message[0u]));

			AGL_CORE_WARNING("{} shader could not be compiled!\n{}", get_shader_name(m_type), message);

			return false;
		}
		return true;
	}

	void sub_shader::create()
	{
		if (is_created())
			destroy();

		AGL_CALL(m_id_object = glCreateShader(m_type));
	}

	void sub_shader::destroy()
	{
		AGL_CALL(glDeleteShader(m_id_object));

		m_type = SHADER_INVALID;
		m_id_object = 0u;
		m_source.clear();
	}
}

