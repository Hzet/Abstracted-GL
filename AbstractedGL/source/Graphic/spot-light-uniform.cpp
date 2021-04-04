#include "spot-light-uniform.hpp"

namespace agl
{
	CSpotLight::CSpotLight(const std::string &name, IUniform const * const parent /*= nullptr*/)
		: IUniformPack(name, parent),
		ambient("ambient", this),
		diffuse("diffuse", this),
		specular("specular", this),
		range("range", this),
		cutOff("cutOff", this),
		direction("direction", this),
		color("color", this)
	{
		addUniform(ambient);
		addUniform(diffuse);
		addUniform(specular);
		addUniform(range);
		addUniform(cutOff);
		addUniform(direction);
		addUniform(color);
	}

	CSpotLight::CSpotLight(CSpotLight &&other)
		: IUniformPack(std::move(other)),
		ambient(std::move(other.ambient)),
		diffuse(std::move(other.diffuse)),
		specular(std::move(other.specular)),
		range(std::move(other.range)),
		cutOff(std::move(other.cutOff)),
		direction(std::move(other.direction)),
		color(std::move(other.color))
	{
		addUniform(ambient);
		addUniform(diffuse);
		addUniform(specular);
		addUniform(range);
		addUniform(cutOff);
		addUniform(direction);
		addUniform(color);
	}

	CSpotLight::CSpotLight(const CSpotLight &other)
		: IUniformPack(other),
		ambient(other.ambient),
		diffuse(other.diffuse),
		specular(other.specular),
		range(other.range),
		cutOff(other.cutOff),
		direction(other.direction),
		color(other.color)
	{
		addUniform(ambient);
		addUniform(diffuse);
		addUniform(specular);
		addUniform(range);
		addUniform(cutOff);
		addUniform(direction);
		addUniform(color);
	}

	std::unique_ptr<agl::IUniform> CSpotLight::clone() const
	{
		return std::unique_ptr<IUniform>(new CSpotLight(*this));
	}
}

