#include "agl/core/app/application.hpp"
#include "agl/graphics/ecs/component/uniform/uniform-build.hpp"
#include "agl/graphics/ecs/system/system-build.hpp"

int main(int argc, char **argv)
{
	try
	{
		auto& app = agl::application::get_instance();

		app.init();
		app.run();

		if (app.is_open())
		{
			app.shutdown();
		}
	}
	catch (std::exception& e)
	{
		AGL_CORE_LOG_ERROR("Exception raised: {}", e.what());
	}
}