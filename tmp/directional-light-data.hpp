#pragma once

#include "shader-data.hpp"
#include <glm/glm.hpp>

namespace agl
{
	/// <summary>
	/// Directional light source is the source that affects every object in the same manner -
	/// it creates an illusion of light source being infinitely far away, so it's beams are parallel to each other.
	/// </summary>
	class CDirLightData
		: public IShaderData
	{
	public:
		CDirLightData() = default;
		CDirLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const glm::vec3 &dir = glm::vec3(0.f), const glm::vec4 &c = glm::vec4(1.f));

		glm::vec3 direction;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

		glm::vec4 color;

	private:
		std::unique_ptr<IShaderData> clone() const override;
		void setData(const std::string &name, const CShader &shader) const override;
	};
}