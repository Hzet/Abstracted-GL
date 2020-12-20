#include "material-data.hpp"
#include "shader-program.hpp"

namespace agl
{
	CMaterial::CMaterial(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s, const float shine)
		: shininess(shine),
		ambient(a),
		diffuse(d),
		specular(s)
	{
	}

	void CMaterial::setData(const std::string &name, const CShader &shader) const
	{
		shader.setFloat(name + ".shininess", shininess);
		shader.setVec4(name + ".ambient", ambient);
		shader.setVec4(name + ".diffuse", diffuse);
		shader.setVec4(name + ".specular", specular);
	}

	std::unique_ptr<IShaderData> CMaterial::clone() const
	{
		return std::unique_ptr<IShaderData>(new CMaterial(*this));
	}
}