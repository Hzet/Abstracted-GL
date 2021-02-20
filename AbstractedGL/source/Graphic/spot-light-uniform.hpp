#pragma once
#include <glm/glm.hpp>

#include "shader-uniform-variable.hpp"
#include "default-agl-shaders.hpp"

namespace agl
{	/// <summary>
	/// Entry representing the spotlight.
	/// All of the sub entries are named same as below.
	/// </summary>
	class CSpotLight
		: public IUniformVariable
	{
	public:
		using IUniformVariable::IUniformVariable;

		/// <summary>
		/// Sets the name of the uniform.
		/// </summary>
		/// <param name="name">The name</param>
		virtual void setName(const std::string &name) override;

		/// <summary>
		/// Sends the members of this uniform to it's destination shader. 
		/// </summary>
		virtual void passToShader() const override;

		/// <summary>
		/// Returns a copy of this instance.
		/// </summary>
		/// <returns></returns>
		virtual std::unique_ptr<IUniform> clone() const override;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

		glm::vec3 range; // constant, linear, quadratic

		glm::vec2 cutOff; // inner, outer

		glm::vec3 direction;
		glm::vec4 color;

	};

}