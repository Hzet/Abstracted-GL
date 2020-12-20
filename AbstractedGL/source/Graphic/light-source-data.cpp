#include "light-source-data.hpp"
#include "shader-program.hpp"

namespace agl
{
	CLightData::CLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s)
		: ambient(a),
		diffuse(d),
		specular(s)
	{
	}

	void CLightData::setData(const std::string &name, const CShader &shader) const
	{
		shader.setVec4(name + ".ambient", specular);
		shader.setVec4(name + ".diffuse", diffuse);
		shader.setVec4(name + ".specular", specular);
	}

	std::unique_ptr<IShaderData> CLightData::clone() const
	{
		return std::unique_ptr<IShaderData>(new CLightData(*this));
	}

}