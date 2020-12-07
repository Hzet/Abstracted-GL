#include "glfw-init.hpp"

#include <cstdint>
#include <GLFW/glfw3.h>

#include "log.hpp"

namespace agl
{
	static void errorCallback(int error, const char *description)
	{
		AGL_CORE_LOG_ERROR("GLFW has failed: [", error, "]\nMessage: ", description);
	}

	bool CGLFWInit::Init()
	{
		std::int32_t result = glfwInit();

		glfwSetErrorCallback(errorCallback);

		return result == GL_TRUE;
	}

	void CGLFWInit::Shutdown()
	{
		glfwTerminate();
	}

}