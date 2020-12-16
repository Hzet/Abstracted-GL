#pragma once
#include <string>
#include <memory>

#include "../System/gl-core.hpp"
#include "../System/move-only.hpp"
#include "../System/event-static-queue.hpp"

#include <GLFW/glfw3.h>
#include <unordered_map>

namespace agl
{
	class CWindowBase
		: public system::CMoveOnly
	{
	public:
		using system::CMoveOnly::CMoveOnly;

		static CWindowBase Create(const std::string &title, const std::uint32_t width, const std::uint32_t height);
		static void SetHint(const std::uint64_t hint, const std::uint64_t value);

		CWindowBase(CWindowBase &&other);
		~CWindowBase();

		bool isOpen();
		void close();

		bool pollEvent(SEvent &event);

		std::int32_t getInputMode(const std::int32_t) const;
		void setInputMode(const std::int32_t mode, const std::int32_t value) const;

	private:
		struct SGLFWwindowDeleter
		{
			void operator()(GLFWwindow *window)	{}
		};

		static std::size_t WindowsCount_;
		static std::unordered_map<std::uint64_t, std::uint64_t> WindowHints_;

		CWindowBase();
		CWindowBase(const std::string &title, std::uint32_t width, std::uint32_t height);

		void shutdown();
		void setGLFWCallbacks();

		const std::string title_;
		std::uint32_t width_;
		std::uint32_t height_;
		system::CEventQueue queue_;
		std::unique_ptr<GLFWwindow, SGLFWwindowDeleter> window_;
	};
}