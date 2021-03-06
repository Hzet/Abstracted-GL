#pragma once

#include "event-types.hpp"

namespace agl
{
	/// <summary>
	/// An aggregation data struct that can contain only one type and only one event data.
	/// </summary>
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
			Keyboard::EKeycode code;
			std::int32_t scancode;
			std::int32_t modifiers;
		};

		struct SMouse
		{
			Mouse::EButton code;
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