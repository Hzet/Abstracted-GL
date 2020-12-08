#pragma once
#include <string>
#include <memory>

#include "../System/gl-core.hpp"
#include "../System/event-static-queue.hpp"

#include <GLFW/glfw3.h>

namespace agl
{
	struct SGLFWwindowDeleter
	{
		void operator()(GLFWwindow *window)
		{
		}
	};

	class CWindow
	{
	public:
		static CWindow Create(const std::string &title, std::uint32_t width, std::uint32_t height);

		CWindow(CWindow &&other);
		~CWindow();

		bool isOpen();
		void close();

		bool pollEvent(SEvent &event);

	private:
		static std::size_t WindowsCount_;

		CWindow();
		CWindow(const std::string &title, std::uint32_t width, std::uint32_t height);

		void shutdown();


		bool move_;
		bool close_;
		const std::string title_;
		std::uint32_t width_;
		std::uint32_t height_;
		agl::CEventQueue queue_;
		std::unique_ptr<GLFWwindow, SGLFWwindowDeleter> window_;
	};
}