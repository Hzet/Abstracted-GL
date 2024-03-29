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
		
		std::vector<glm::vec4> get_colors(glm::vec4 const& c) const;

		virtual gl_draw_type get_draw_type() const = 0;
		virtual std::uint64_t get_vertex_count() const = 0;
		virtual std::uint64_t get_index_count() const = 0;
		virtual std::vector<glm::vec3> get_positions() const = 0;
		virtual std::vector<std::uint32_t> get_indices() const = 0;

	private:
		color m_color;
	};
}