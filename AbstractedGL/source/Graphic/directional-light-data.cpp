#include "directional-light-data.hpp"
#include "shader-program.hpp"

namespace agl
{

	CDirLightData::CDirLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const glm::vec3 &dir, const glm::vec4 &c /*= glm::vec4(1.f)*/)
		: ambient(a),
		diffuse(d),
		specular(s),
		direction(dir),
		color(c)
	{
	}

	std::unique_ptr<IShaderData> CDirLightData::clone() const
	{
		return std::unique_ptr<IShaderData>(new CDirLightData(*this));
	}

	void CDirLightData::setData(const std::string &name, const CShader &shader) const
	{
		shader.setVec3(name + ".direction", direction);
		shader.setVec4(name + ".ambient", ambient);
		shader.setVec4(name + ".diffuse", diffuse);
		shader.setVec4(name + ".specular", specular);
		shader.setVec4(name + ".color", color);
	}

}