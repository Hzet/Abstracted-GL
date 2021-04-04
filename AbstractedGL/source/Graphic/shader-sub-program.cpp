#include "shader-sub-program.hpp"

#include <fstream>

#include "../System/gl-core.hpp"
#include "../System/error.hpp"
#include "../System/error-code.hpp"
#include <cerrno>

namespace agl
{
	namespace graphics
	{
		static const char* getShaderName(std::uint64_t type)
		{
			switch (type)
			{
			case GL_VERTEX_SHADER: return "vertex";
			case GL_TESS_CONTROL_SHADER: return "tessellation control";
			case GL_TESS_EVALUATION_SHADER: return "tessellation evaluation";
			case GL_GEOMETRY_SHADER: return "geometry";
			case GL_FRAGMENT_SHADER: return "fragment";
			case GL_COMPUTE_SHADER: return "compute";
			}

			return "invalid";
		}

		static bool VerifyType(const std::uint64_t type)
		{
			switch (type)
			{
			case GL_VERTEX_SHADER: return true;
			case GL_TESS_CONTROL_SHADER: return true;
			case GL_TESS_EVALUATION_SHADER: return true;
			case GL_GEOMETRY_SHADER: return true;
			case GL_FRAGMENT_SHADER: return true;
			case GL_COMPUTE_SHADER: return true;
			}

			return false;
		}

		CSubShader::CSubShader()
			: type_(0u)
		{
		}

		CSubShader::~CSubShader()
		{
			if (!isMoveConstructing())
				destroy();
		}

		std::uint32_t CSubShader::getID() const
		{
			return objectID_;
		}

		std::uint64_t CSubShader::getType() const
		{
			return type_;
		}

		bool CSubShader::loadFromFile(const std::uint64_t type, const std::string &filename)
		{
			std::ifstream file(filename, std::ios::in | std::ios::beg);

			if (!file.is_open())
			{
				AGL_CORE_ERROR("\nFilename: {} {}", error::OPEN_FILE, filename);
				return false;
			}

			source_ = "";
			std::string line;

			while (std::getline(file, line))
				source_ += line + '\n';

			file.close();

			type_ = type;

			return true;
		}

		bool CSubShader::loadFromMemory(const std::uint64_t type, const char *source, std::uint64_t size)
		{
			if (source == nullptr)
				return false;

			source_.resize(size);
			for (std::uint64_t i = 0u; i < size; i++)
				source_[i] = *(source + i);

			source_ += '\0';

			type_ = type;

			return true;
		}

		bool CSubShader::setSource(const std::uint64_t type, const std::string &source)
		{
			if (source.empty())
				return false;

			source_ = source;
			type_ = type;

			return true;
		}

		bool CSubShader::compile()
		{
			if (source_.empty())
			{
				AGL_CORE_ERROR("Shader [{}] source code has not been loaded!", error::INVALID_VALUE, getShaderName(type_));
				return false;
			}

			if (!VerifyType(type_))
			{
				AGL_CORE_ERROR("Invalid shader sub-program type! [{}]", error::INVALID_VALUE, type_);
				return false;
			}

			const char *source = source_.c_str();

			create();
			AGL_CALL(glShaderSource(objectID_, 1u, &source, NULL));
			AGL_CALL(glCompileShader(objectID_));

			std::int32_t result;

			AGL_CALL(glGetShaderiv(objectID_, GL_COMPILE_STATUS, &result));

			if (!result)
			{
				std::int32_t length;
				std::string message;
				AGL_CALL(glGetShaderiv(objectID_, GL_INFO_LOG_LENGTH, &length));

				message.resize(length);
				AGL_CALL(glGetShaderInfoLog(objectID_, length, nullptr, &message[0u]));

				AGL_CORE_ERROR("Shader [{}] sub program could not be compiled!\n{}", error::SUBSHADER_COMPILE, getShaderName(type_), message);

				return false;
			}
			return true;
		}

		void CSubShader::create()
		{
			if (isCreated())
				destroy();

			AGL_CALL(objectID_ = glCreateShader(type_));
		}

		void CSubShader::destroy()
		{
			AGL_CALL(glDeleteShader(objectID_));

			type_ = 0u;
			objectID_ = 0u;
			source_.clear();
		}
	}
}

