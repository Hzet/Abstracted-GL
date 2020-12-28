#pragma once

#include "shape.hpp"

namespace agl
{
	template<class... Args>
	class CLightSource
		: public CShape<Args...>
	{
	public:
		void setLightColor(const glm::vec4 &color);
		const glm::vec4& getLightColor() const;

		void setDirection(const glm::vec3 &direction);
		const glm::vec3& getDirection() const;

	private:
		glm::vec4 lightColor_;
		glm::vec3 lightDirection_;
	};

	template<class... Args>
	void CLightSource<Args...>::setLightColor(const glm::vec4 &color)
	{
		lightColor_ = color;
	}
	template<class... Args>
	const glm::vec4& CLightSource<Args...>::getLightColor() const
	{
		return lightColor_;
	}

	template<class... Args>
	void CLightSource<Args...>::setDirection(const glm::vec3 &direction)
	{
		lightDirection_ = direction;
	}

	template<class... Args>
	const glm::vec3& CLightSource<Args...>::getDirection() const
	{
		return lightDirection_;
	}
}