#pragma once 

#include "mesh.hpp"
#include "spot-light-uniform.hpp"
#include "default-agl-shaders.hpp"

namespace agl
{
	template <class... Args>
	class CLight
		: public CMesh<Args...>
	{
	public:
		CLight();
		CLight(CLight &&other);
		CLight(const CLight &other);
		virtual ~CLight() = default;

		CLight& operator=(CLight &&other) = default;
		CLight& operator=(const CLight &other) = default;
		
		virtual void draw(const CRenderer &renderer) const override;

		CSpotLight spotLight;
		CUniform<const glm::vec3&, const CTransformable&> position;
	};

#include "light.inl"
}