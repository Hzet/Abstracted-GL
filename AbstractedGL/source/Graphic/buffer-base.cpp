#include "buffer-base.hpp"
#include <utility>

namespace agl
{
	namespace graphics
	{
		CBufferBase::CBufferBase()
			: bufferID_(0u)
		{
		}

		bool CBufferBase::isRegistered() const
		{
			return bufferID_ != 0u;
		}
	}
}