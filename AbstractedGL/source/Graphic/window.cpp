#include "window.hpp"
#include "drawable.hpp"

#include "../System/gl-core.hpp"

namespace agl
{
	CWindow::CWindow(const std::string &title, const std::uint32_t width, const std::uint32_t height)
		: CWindowBase(std::move(CWindowBase::Create(title, width, height)))
	{
	}

	void CWindow::draw(const IDrawable &drawable) const
	{
		drawable.draw(*this);
	}

	void CWindow::clear(glm::vec4 color) const
	{
		AGL_CALL(glClearColor(color.x, color.y, color.z, color.w));
	}

	void CWindow::clearBit(std::uint64_t bits) const
	{
		AGL_CALL(glClear(bits));
	}
}

