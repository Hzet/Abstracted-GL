#pragma once
#include <vector>

#include "agl/graphics/types/types.hpp"
#include "agl/core/enums/gl-draw-type.hpp"

namespace agl
{
	class shape_builder
	{
	public:
		virtual ~shape_builder() = default;

		void set_color(color const& c);
		color const& get_color() const;

		virtual gl_draw_type get_draw_type() const = 0;
		virtual std::uint64_t get_vertex_count() const = 0;
		virtual std::uint64_t get_index_count() const = 0;
		virtual std::vector<position> get_positions() const = 0;
		virtual std::vector<std::uint32_t> get_indices() const = 0;
		virtual std::vector<color> get_colors() const = 0;

	private:
		color m_color;
	};
}