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

		virtual std::unique_ptr<IUniform> clone() const override;

		TUniform<glm::vec4> ambient;
		TUniform<glm::vec4> diffuse;
		TUniform<glm::vec4> specular;

		TUniform<glm::vec3> range; // constant, linear, quadratic

		TUniform<glm::vec2> cutOff; // inner, outer

		TUniform<glm::vec3> direction;
		TUniform<glm::vec4> color;
	};

}