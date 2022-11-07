#include "agl/core/app/layer-manager.hpp"

namespace agl
{
	std::uint64_t layer_manager::get_count() const
	{
		return m_layers.get_count();
	}

	layer_base& layer_manager::operator[](std::uint64_t index)
	{
		return *m_layers.get(index);
	}

	layer_base const& layer_manager::operator[](std::uint64_t index) const
	{
		return *m_layers.get(index);
	}
}