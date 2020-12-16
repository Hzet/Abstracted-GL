#pragma once

#include "window-base.hpp"
#include "renderer.hpp"
#include "camera-base.hpp"

namespace agl
{
	struct IDrawable;

	class CWindow
		: public CWindowBase,	
		public CRenderer
	{
	public:
		CWindow(const std::string &title, const std::uint32_t width, const std::uint32_t height);

		void draw(const IDrawable &drawable) const;

		void clear(glm::vec4 color) const;
		void clearBit(std::uint64_t bits) const;

		ICamera& getCamera();
		void setCamera(const ICamera &camera);

	private:

	};
}