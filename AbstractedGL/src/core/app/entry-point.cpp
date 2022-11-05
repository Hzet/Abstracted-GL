#include "agl/core/app/application.hpp"

int main(int argc, char **argv)
{
	try
	{
		auto& app = agl::application::get_instance();

		app.run();

		app.shutdown();
	}
	catch (std::exception& e)
	{
		AGL_CORE_LOG_ERROR("Exception raised: {}", e.what());
	}
}