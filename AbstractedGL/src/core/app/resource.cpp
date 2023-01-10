#include "agl/core/app/resource.hpp"

namespace agl
{
	resource::~resource()
	{
		reset();
	}

	void resource::reset()
	{
		if (!is_any())
			return;

		m_destructor->destruct_element(m_buffer.data());
		m_buffer.clear();
	}

	bool resource::is_any() const
	{
		return !m_buffer.empty();
	}

	resource_type_uid resource::get_id() const
	{
		return m_id;
	}
}

