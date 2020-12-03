#pragma once

#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include "../System/event-static-queue.hpp"

namespace agl
{
	class CWindowBase
	{
	public:
		static CWindowBase Create(const std::string &title, std::uint32_t width, std::uint32_t height);

		CWindowBase(CWindowBase &&other);
		~CWindowBase();

	private:
		static std::size_t WindowsCount_;

		CWindowBase();
		CWindowBase(const std::string &title, std::uint32_t width, std::uint32_t height);

		const std::string title_;
		std::uint32_t width_;
		std::uint32_t height_;
		agl::CEventQueue queue_;
		std::unique_ptr<GLFWwindow> window_;
	};
}