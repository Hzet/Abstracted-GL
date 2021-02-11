#include "point-light-data.hpp"
#include "shader-program.hpp"
#include "glm/ext.hpp"

namespace agl
{

	CPointLightData::CPointLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const glm::vec3 &r, const float icutoff /*= 180.f*/, const float ocutoff /*= 180.f*/, const glm::vec3 &dir /*= glm::vec3(0.f)*/, const glm::vec3 &pos /*= glm::vec3(0.f)*/, const glm::vec4 &c /*= glm::vec4(1.f)*/)
		: ambient(a),
		diffuse(d),
		specular(s),
		range(r),
		innerCutOff(glm::cos(glm::radians(icutoff))),
		outerCutOff(glm::cos(glm::radians(ocutoff))),
		position(pos),
		direction(dir),
		color(c)
	{
	}

	std::unique_ptr<IShaderData> CPointLightData::clone() const
	{
		return std::unique_ptr<IShaderData>(new CPointLightData(*this));
	}

	void CPointLightData::setData(const std::string &name, const CShader &shader) const
	{
		shader.setVec4(name + ".ambient", ambient);
		shader.setVec4(name + ".diffuse", diffuse);
		shader.setVec4(name + ".specular", specular);
		shader.setFloat(name + ".constant", range.x);
		shader.setFloat(name + ".linear", range.y);
		shader.setFloat(name + ".quadratic", range.z);
		shader.setFloat(name + ".innerCutOff", innerCutOff);
		shader.setFloat(name + ".outerCutOff", outerCutOff);
		shader.setVec3(name + ".position", position);
		shader.setVec3(name + ".direction", direction);
		shader.setVec4(name + ".color", color);
	}

}

