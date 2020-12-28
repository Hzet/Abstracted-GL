#pragma once

#include <glm/glm.hpp>

#include "shader-data.hpp"

namespace agl
{
	/// <summary>
	/// A point light data represents the type of light that loses its strength over distance.
	/// The light is lightening objects which are placed on it's trajectory.
	/// The main beam has reach of 'innerCutOff' degrees, then the light is diffused up to 'outerCutOff'.
	/// The strength of the light beams over distance is calculated with this equation:
	///			 1.f
	/// --------------------------
	/// KC + KL * d + KQ * (d ^ 2)
	/// where:
	/// KC - constant (range.x)
	/// KL - linear (range.y)
	/// KQ - quadratic (range.z)
	/// d - distance between the light source and the object vertex
	/// </summary>
	class CPointLightData
		: public IShaderData
	{
	public:
		CPointLightData() = default;
		CPointLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const glm::vec3 &r, const float icutoff = 180.f, const float ocutoff = 180.f, const glm::vec3 &dir = glm::vec3(0.f), const glm::vec3 &pos = glm::vec3(0.f), const glm::vec4 &c = glm::vec4(1.f));

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

		glm::vec3 range; // constant, linear, quadratic

		float innerCutOff;
		float outerCutOff;

		glm::vec3 direction;
		glm::vec3 position;
		glm::vec4 color;

	private:
		std::unique_ptr<IShaderData> clone() const override;

		void setData(const std::string &name, const CShader &shader) const override;
	};
}