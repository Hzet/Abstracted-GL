#include "graphics/render/vertex-layout.hpp"
#include "system/debug/assert.hpp"

namespace agl
{
	vertex_layout::vertex_layout()
		: m_stride(0ul)
	{
	}

	std::uint32_t vertex_layout::get_size() const
	{
		return m_stride;
	}

	std::uint32_t vertex_layout::get_count() const
	{
		return m_elements.size();
	}

	const vertex_layout::element& vertex_layout::operator[](const std::uint32_t index) const
	{
		AGL_CORE_ASSERT(index < m_elements.size(), "Index out of bounds!");

		return m_elements[index];
	}
}