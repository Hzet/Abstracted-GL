#include "system/glcore/gl-object.hpp"

namespace agl
{
	gl_object::gl_object()
		: m_id_object(0u)
	{
	}

	bool gl_object::is_created() const
	{
		return m_id_object != 0u;
	}
}

