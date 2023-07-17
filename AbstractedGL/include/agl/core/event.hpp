#pragma once
#include "agl/core/event-types.hpp"

namespace agl
{
	/// <summary>
	/// An aggregation data struct that can contain only one type and only one event data.
	/// </summary>
	struct event
	{
		struct position_factor
		{
			float x;
			float y;
		};

		struct size_factor
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		struct scroll_factor
		{
			float x;
			float y;
		};

		struct keyboard
		{
			key_type code;
			std::int32_t scancode;
			std::int32_t modifiers;
		};

		struct mouse
		{
			button_type code;
			std::int32_t bit_modifiers;
		};

		struct scale_factor
		{
			float x;
			float y;
		};

		event_type type = INVALID_EVENT;

		union
		{
			position_factor	position;
			size_factor size;
			scroll_factor scroll;
			keyboard key;
			mouse button;
			scale_factor scale;
			std::uint32_t character;
		};
	};
}