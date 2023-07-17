#include "agl/system/glcore/destructive-move.hpp"

namespace agl
{
	destructive_move::destructive_move()
		: m_moving(false)
	{
	}

	destructive_move::destructive_move(destructive_move &&other)
	{
		other.m_moving = true;
	}

	bool destructive_move::is_move_constructing() const
	{
		return m_moving;
	}
}

