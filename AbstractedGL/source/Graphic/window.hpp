#pragma once

#include "window-base.hpp"
#include "renderer.hpp"
#include "camera-base.hpp"

namespace agl
{
	struct IDrawable;

	/// <summary>
	/// A class that is a combination of the CWindowBase and the CRenderer classes.
	/// </summary>
	class CWindow
		: public CWindowBase,	
		public CRenderer
	{
	public:
		/// <summary>
		/// Create the window.
		/// </summary>
		/// <param name="title">The title</param>
		/// <param name="width">The width</param>
		/// <param name="height">The height</param>
		CWindow(const std::string &title, const std::uint32_t width, const std::uint32_t height);

		/// <summary>
		/// Draw 'drawable' object.
		/// </summary>
		/// <param name="drawable">The object to draw</param>
		void draw(const IDrawable &drawable) const;

		/// <summary>
		/// Clear window's screen with a color.
		/// </summary>
		/// <param name="color">The color</param>
		void clear(glm::vec4 color) const;

		/// <summary>
		/// Select the buffers to be cleared.
		/// </summary>
		/// <param name="bits"></param>
		void clearBit(std::uint64_t bits) const;
//	private:

	};
}