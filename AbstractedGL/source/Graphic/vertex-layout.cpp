#include "vertex-layout.hpp"

namespace agl
{
	std::uint64_t CVertexLayout::getStride() const
	{
		return stride_;
	}

	std::uint64_t CVertexLayout::getCount() const
	{
		return elements_.size();
	}

	const agl::CVertexLayout::SElement& CVertexLayout::operator[](const std::uint64_t index) const
	{
		return elements_[index];
	}

	CVertexLayout::SElement::SElement()
	{
	}
}