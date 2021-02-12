#include "destructive-move.hpp"

namespace agl
{
	namespace system
	{
		CDestructiveMove::CDestructiveMove()
			: move_(false)
		{
		}

		CDestructiveMove::CDestructiveMove(CDestructiveMove &&other)
		{
			other.move_ = true;
		}

		bool CDestructiveMove::isMoveConstructing() const
		{
			return move_;
		}
	}
}

