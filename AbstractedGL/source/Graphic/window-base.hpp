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
	/// <summary>
	/// A base window class that acts like a wrapper over GLFW's window related functions.
	/// </summary>
	class CWindowBase
		: public system::CMoveOnly
	{
	public:
		using system::CMoveOnly::CMoveOnly;

		/// <summary>
		/// Create the window and set the it's context as current.
		/// If this is the first ever call of this method, it initializes the GLFW.
		/// It may throw AGL exception after failing to initialize the window, GLFW or GLAD.
		/// </summary>
		/// <param name="title">The title</param>
		/// <param name="width">The width</param>
		/// <param name="height">The height</param>
		/// <returns>
		/// A newly created window
		/// </returns>
		static CWindowBase Create(const std::string &title, const std::uint32_t width, const std::uint32_t height);

		/// <summary>
		/// Set the window hint.
		/// The call must be preceding the call to create the window.
		/// </summary>
		/// <param name="hint">Hint name</param>
		/// <param name="value">Hint value</param>
		static void SetHint(const std::uint64_t hint, const std::uint64_t value);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">other object</param>
		CWindowBase(CWindowBase &&other);

		/// <summary>
		/// Destroy the window or/and uninitialize GLFW.
		/// </summary>
		~CWindowBase();

		/// <summary>
		/// Check whether the window is open.
		/// Updates the buffer and polls events.
		/// </summary>
		/// <returns>
		/// True - window is open
		/// False - window is closed
		/// </returns>
		bool isOpen();

		/// <summary>
		/// Close the window.
		/// </summary>
		void close();

		/// <summary>
		/// Get the last event and save it in 'event' parameter.
		/// </summary>
		/// <param name="event">The output event</param>
		/// <returns>
		/// True - more events left to be read
		/// False - no more events left to be read
		/// </returns>
		bool pollEvent(SEvent &event);

		/// <summary>
		/// Return the input mode.
		/// </summary>
		/// <returns>
		/// The mode
		/// </returns>
		std::int32_t getInputMode() const;

		/// <summary>
		/// Set the input 'mode' to be 'value'.
		/// </summary>
		/// <param name="mode">The mode</param>
		/// <param name="value">The value</param>
		void setInputMode(const std::int32_t mode, const std::int32_t value) const;

	private:
		/// <summary>
		/// A custom deleter to store GLFWwindow as unique_ptr
		/// </summary>
		struct SGLFWwindowDeleter
		{
			void operator()(GLFWwindow *window)	{}
		};

		static std::size_t WindowsCount_;
		static std::unordered_map<std::uint64_t, std::uint64_t> WindowHints_;

		/// <summary>
		/// Default constructor.
		/// </summary>
		CWindowBase() = default;

		/// <summary>
		/// Parameterized constructor. 
		/// Increment the 'WindowsCount_'.
		/// </summary>
		/// <param name="title">The title</param>
		/// <param name="width">The width</param>
		/// <param name="height">The height</param>
		CWindowBase(const std::string &title, std::uint32_t width, std::uint32_t height);

		/// <summary>
		/// Destroy the window and uninitialize the GLFW.
		/// </summary>
		void shutdown();

		/// <summary>
		/// Set the GLFW window's callbacks.
		/// </summary>
		void setGLFWCallbacks();

		const std::string title_;
		std::uint32_t width_;
		std::uint32_t height_;
		system::CEventQueue queue_;
		std::unique_ptr<GLFWwindow, SGLFWwindowDeleter> window_;
	};
}