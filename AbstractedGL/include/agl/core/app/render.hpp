#pragma once
#include <glm/glm.hpp>

namespace agl
{
	class render
	{
	public:
		const glm::vec4& get_clear_color() const;
		void set_clear_color(const glm::vec4 &color);

		std::uint32_t get_clear_flags() const;
		void set_clear_flags(std::uint32_t flags);



	private:
		glm::vec4 m_clear_color;
		std::uint32_t m_clear_flags;
	};
}

