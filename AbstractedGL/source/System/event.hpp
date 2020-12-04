#pragma once

#include "event-types.hpp"

namespace agl
{
	struct SEvent
	{
		struct SPosition
		{
			double x;
			double y;
		};

		struct SSize
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		struct SScroll
		{
			double x;
			double y;
		};

		struct SKeyboard
		{
			Event::EKeycode code;
			std::int32_t scancode;
			std::int32_t modifiers;
		};

		struct SMouse
		{
			Event::EButton code;
			std::int32_t bit_modifiers;
		};

		struct SScale
		{
			float x;
			float y;
		};

		Event::EType type = Event::INVALID_EVENT;

		union
		{
			SPosition	   position;
			SSize		   size;
			SScroll		   scroll;
			SKeyboard	   key;
			SMouse		   button;
			SScale		   scale;
			std::uint32_t  character;
		};
	};
}