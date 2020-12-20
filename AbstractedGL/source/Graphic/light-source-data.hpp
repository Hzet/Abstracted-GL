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
		CLightData(const glm::vec4 &a, const glm::vec4 &d, const glm::vec4 &s);

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

	private:		
		virtual void setData(const std::string &name, const CShader &shader) const override;

		virtual std::unique_ptr<IShaderData> clone() const override;
	};
}