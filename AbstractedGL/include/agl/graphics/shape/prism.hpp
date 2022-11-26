#pragma once
#include "agl/graphics/shape/shape-builder.hpp"

namespace agl
{
	struct prism
	{
		float radius;
		glm::vec2 side_size;
		std::uint64_t side_count;
	};

	class prism_builder
		: public shape_builder
	{
	public:
		prism_builder() = default;
		prism_builder(std::uint64_t sides_count, float radius, float height);

		virtual gl_draw_type get_draw_type() const override;
		virtual std::uint64_t get_vertex_count() const override;
		virtual std::uint64_t get_index_count() const override;
		virtual std::vector<std::uint32_t> get_indices() const override;
		virtual std::vector<position> get_positions() const override;

	private:
		prism m_specification;
	};
}