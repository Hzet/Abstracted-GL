#include "agl/utility/ecs/signature.hpp"

namespace agl
{
	bool operator==(const signature &l, const signature &r)
	{
		return l.m_signature == r.m_signature;
	}

	bool operator!=(const signature &l, const signature &r)
	{
		return !(l == r);
	}

	std::uint64_t signature::get_index(component_type_uid id_component_type)
	{
		return id_component_type - 1ul;
	}

	signature::signature()
		: m_peak(-1)
	{
	}

	bool signature::operator[](component_type_uid id_component_type) const
	{
		return m_signature[get_index(id_component_type)];
	}

	bool signature::operator[](std::uint64_t index) const
	{
		return m_signature[index];
	}

	std::uint64_t signature::get_count() const
	{
		return (m_peak == -1 ? 0ul : m_peak + 1ul);
	}

	const std::bitset<AGL_MAX_COMPONENTS>& signature::bitset() const
	{
		return m_signature;
	}
}