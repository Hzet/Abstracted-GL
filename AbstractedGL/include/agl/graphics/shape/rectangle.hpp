#pragma once
#include "agl/graphics/shape/shape-builder.hpp"

namespace agl
{
	struct rectangle
	{
		glm::vec2 size;
	};

	class rectangle_builder
		: public shape_builder
	{
	public:
		rectangle_builder() = default;
		rectangle_builder(rectangle const& rect);

		virtual gl_draw_type get_draw_type() const override;
		virtual std::uint64_t get_vertex_count() const override;
		virtual std::uint64_t get_index_count() const override;
		virtual std::vector<std::uint32_t> get_indices() const override;
		virtual std::vector<position> get_positions() const override;
		virtual std::vector<color> get_colors() const override;

	private:
		rectangle m_specification;
	};
}