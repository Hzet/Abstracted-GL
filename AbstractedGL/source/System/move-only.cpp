#include "move-only.hpp"

namespace agl
{
	namespace system
	{
		CMoveOnly::CMoveOnly()
			: move_(false)
		{
		}

		CMoveOnly::CMoveOnly(CMoveOnly &&other)
		{
			other.move_ = true;
		}

		bool CMoveOnly::isMoveConstructing() const
		{
			return move_;
		}
	}
}

