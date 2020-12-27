#include "light-source-data.hpp"
#include "shader-program.hpp"

namespace agl
{
	CLightData::CLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const glm::vec3 &p, const float c, const float l, const float q, float cut, const glm::vec4 &dir)
		: ambient(a),
		diffuse(d),
		specular(s),
		position(p),
		constant(c),
		linear(l),
		quadratic(q),
		direction(dir),
		cutOff(glm::cos(glm::radians(cut)))
	{
	}

	void CLightData::setData(const std::string &name, const CShader &shader) const
	{
		shader.setVec4(name + ".ambient", ambient);
		shader.setVec4(name + ".diffuse", diffuse);
		shader.setVec4(name + ".specular", specular);
		shader.setVec3(name + ".position", position);
		shader.setVec4(name + ".direction", direction);
		shader.setFloat(name + ".constant", constant);
		shader.setFloat(name + ".linear", linear);
		shader.setFloat(name + ".quadratic", quadratic);
		shader.setFloat(name + ".cutOff", cutOff);
	}

	std::unique_ptr<IShaderData> CLightData::clone() const
	{
		return std::unique_ptr<IShaderData>(new CLightData(*this));
	}

}