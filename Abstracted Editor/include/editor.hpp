#pragma once
#include "agl/core/app/application.hpp"

namespace editor
{
	class editor_application
		: public agl::application
	{
	public:
		virtual void init() override;
	};
}
