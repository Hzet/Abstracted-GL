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

		CUniform<glm::vec3> direction;

		CUniform<glm::vec4> ambient;
		CUniform<glm::vec4> diffuse;
		CUniform<glm::vec4> specular;

		CUniform<glm::vec4> color;
	};
}