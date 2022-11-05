#pragma once
#include "agl/graphics/ecs/component/mesh.hpp"

namespace agl
{
	class prism
	{
	public:
		prism() = default;
		prism(shader_uid id_shader);
		
		void set_radius(float radius);
		float get_radius() const;
		void set_height(float height);
		float get_height() const;
		void set_width(float width);
		float get_width() const;

		void set_sides(glm::vec2 const& sides);
		glm::vec2 const& get_sides() const;

		void set_side_count(float count);
		float get_side_count() const;

		void set_color(agl::color const& color);

		shader_uid get_shader_uid() const;
		void set_shader_uid(shader_uid id_shader);

	private:
		mesh m_mesh;
		float m_radius;
		glm::vec2 m_sides;
		std::uint64_t m_sides_count;

	private: 
		friend class render_system;
	};
}