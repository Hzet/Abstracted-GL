#pragma once 

#include <cstdint>

namespace agl
{
	namespace Error
	{
		enum EError: std::uint64_t
		{
			OPEN_FILE		= 0x201,
			READ_FILE		= 0x202,
			WRITE_FILE		= 0x203,
			GLFW_FAILURE	= 0x204,
			GLAD_FAILURE	= 0x205,
			OPENGL_FAILURE  = 0x206
		};
	}
}