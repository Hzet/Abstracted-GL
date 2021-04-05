#pragma once 
#include <glm/glm.hpp>

#include "shader-uniform-variable.hpp"
#include "shader-uniform-pack.hpp"

namespace agl
{
	/// <summary>
	/// Entry representing the directional light.
	/// All of the sub entries are named same as below.
	/// </summary>
	class CDirectionalLight
		: public IUniformPack
	{
	public:
		CDirectionalLight(const std::string &name, IUniform const * const parent = nullptr);
		CDirectionalLight(CDirectionalLight &&other);
		CDirectionalLight(const CDirectionalLight &other);

		CDirectionalLight& operator=(CDirectionalLight &&other) = default;
		CDirectionalLight& operator=(const CDirectionalLight &other) = default;

		virtual std::unique_ptr<IUniform> clone() const override;

		TUniform<glm::vec3> direction;

		TUniform<glm::vec4> ambient;
		TUniform<glm::vec4> diffuse;
		TUniform<glm::vec4> specular;

		TUniform<glm::vec4> color;
	};
}