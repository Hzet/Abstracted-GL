#include "shader-sub-program.hpp"

#include <fstream>

#include "../System/gl-core.hpp"
#include "../System/error.hpp"
#include "../System/core-error-codes.hpp"

namespace agl
{
	namespace graphics
	{
		bool CSubShader::VerifyType(const std::uint64_t type)
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
			: programID_(0u),
			type_(0u)
		{
		}

		CSubShader::~CSubShader()
		{
			if(!isMoveConstructing())
				destroy();
		}

		std::uint32_t CSubShader::getID() const
		{
			return programID_;
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
				AGL_CORE_ERROR("\nFilename: {}", Error::OPEN_FILE, filename);
				return false;
			}

			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			source_ = "";
			std::string line;
			try
			{
				while (std::getline(file, line))
					source_ += line + '\n';

				file.close();
			}
			catch (std::ifstream::failure &e)
			{
				AGL_CORE_ERROR("Filename: {}\nAt position: {}\n{}", Error::READ_FILE, filename, source_.size(), e.what());
				file.close();

				return false;
			}

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

			return true;
		}

		bool CSubShader::setSource(const std::uint64_t type, const std::string &source)
		{
			if (source.empty())
				return false;

			source_ = source;
			return true;
		}

		bool CSubShader::compile()
		{
			if (source_.empty())
			{
				AGL_CORE_ERROR("Shader source code has not been loaded!", Error::INVALID_VALUE);
				return false;
			}

			if (!VerifyType(type_))
			{
				AGL_CORE_ERROR("Invalid shader sub-program type! [{}]", Error::INVALID_VALUE, type_);
				return false;
			}

			const char *source = source_.c_str();

			AGL_CALL(programID_ = glCreateShader(type_));
			AGL_CALL(glShaderSource(programID_, 1u, &source, NULL));
			AGL_CALL(glCompileShader(programID_));

			std::int32_t result;

			AGL_CALL(glGetShaderiv(programID_, GL_COMPILE_STATUS, &result));

			if (!result)
			{
				std::int32_t length;
				std::string message;
				AGL_CALL(glGetShaderiv(programID_, GL_INFO_LOG_LENGTH, &length));

				message.resize(length);
				AGL_CALL(glGetShaderInfoLog(programID_, length, nullptr, &message[0u]));

				AGL_CORE_ERROR("Shader sub program could not be compiled!\n{}", Error::SUBSHADER_COMPILE, message);

				return false;
			}
			return true;
		}

		void CSubShader::destroy()
		{
			AGL_CALL(glDeleteShader(programID_));
		}
	}
}

