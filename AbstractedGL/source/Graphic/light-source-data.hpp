#pragma once

#include "shader-data.hpp"

#include <glm/glm.hpp>

namespace agl
{
	class CLightData final
		: public IShaderData
	{
	public:
		CLightData() = default;
		CLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const glm::vec3 &p, const float c, const float l, const float q, float cut = 360.f, const glm::vec4 &dir = glm::vec4(0.f));

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

		glm::vec3 position;
		glm::vec4 direction;

		float constant;
		float linear;
		float quadratic;

		float cutOff;

	private:		
		virtual void setData(const std::string &name, const CShader &shader) const override;

		virtual std::unique_ptr<IShaderData> clone() const override;
	};
}