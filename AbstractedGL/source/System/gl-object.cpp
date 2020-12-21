#include "gl-object.hpp"

namespace agl
{
	namespace system
	{
		IGLObject::IGLObject()
			: objectID_(0u)
		{
		}

		bool IGLObject::isCreated() const
		{
			return objectID_ != 0u;
		}
	}
}

