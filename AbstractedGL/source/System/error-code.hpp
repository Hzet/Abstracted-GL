#pragma once 

namespace agl
{
	namespace error
	{
		enum EError : std::uint64_t
		{
			NO_CODE = 0,
			OPEN_FILE,
			READ_FILE,
			WRITE_FILE,
			GLFW_FAILURE,
			GLAD_FAILURE,
			OPENGL_FAILURE,
			INVALID_VALUE,
			SUBSHADER_COMPILE,
			SHADER_COMPILE,
			SHADER_LINK,
			IMPORT_DATA,
			EXPORT_DATA
		};

		constexpr const char* getErrorMessage(const EError code)
		{
			switch (code)
			{
			case NO_CODE: return "This error has no error code provided";
			case OPEN_FILE: return "Failed to open a file";
			case READ_FILE: return "Failed to read from a file";
			case WRITE_FILE: return "Failed to write to a file";
			case GLFW_FAILURE: return "GLFW has failed to execute call";
			case GLAD_FAILURE: return "GLAD has failed to execute call";
			case OPENGL_FAILURE: return "OpenGL has failed to execute call";
			case INVALID_VALUE: return "Function was provided with an invalid value";
			case SUBSHADER_COMPILE: return "Shader sub-program has failed to compile";
			case SHADER_COMPILE: return "Shader program has failed to compile";
			case SHADER_LINK: return "Shader program has failed to link";
			case IMPORT_DATA: return "Failed to import the data";
			case EXPORT_DATA: return "Failed to export the data";
			}
			return "Unknown error!";
		}
	}
}