#pragma once
#include <glm/glm.hpp>

#include "shader-uniform-variable.hpp"
#include "shader-uniform-pack.hpp"
#include "default-agl-shaders.hpp"

namespace agl
{	/// <summary>
	/// Entry representing the spotlight.
	/// All of the sub entries are named same as below.
	/// </summary>
	class CSpotLight
		: public IUniformPack
	{
	public:
		//using IUniformPack::IUniformPack;

		CSpotLight(const std::string &name, IUniform const * const parent = nullptr);
		CSpotLight(CSpotLight &&other);
		CSpotLight(const CSpotLight &other);

		CSpotLight& operator=(CSpotLight &&other) = default;
		CSpotLight& operator=(const CSpotLight &other) = default;

		CUniform<glm::vec4> ambient;
		CUniform<glm::vec4> diffuse;
		CUniform<glm::vec4> specular;

		CUniform<glm::vec3> range; // constant, linear, quadratic

		CUniform<glm::vec2> cutOff; // inner, outer

		CUniform<glm::vec3> direction;
		CUniform<glm::vec4> color;
	};

}