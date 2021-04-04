#include "directional-light-uniform.hpp"
#include "default-agl-shaders.hpp"

namespace agl
{
	CDirectionalLight::CDirectionalLight(const std::string &name, IUniform const * const parent /*= nullptr*/)
		: IUniformPack(name, parent),
		ambient("ambient", this),
		diffuse("diffuse", this),
		specular("specular", this),
		direction("direction", this),
		color("color", this)
	{
		addUniform(ambient);
		addUniform(diffuse);
		addUniform(specular);
		addUniform(direction);
		addUniform(color);
	}

	CDirectionalLight::CDirectionalLight(CDirectionalLight &&other)
		: IUniformPack(std::move(other)),
		ambient(std::move(other.ambient)),
		diffuse(std::move(other.diffuse)),
		specular(std::move(other.specular)),
		direction(std::move(other.direction)),
		color(std::move(other.color))
	{
		addUniform(ambient);
		addUniform(diffuse);
		addUniform(specular);
		addUniform(direction);
		addUniform(color);
	}

	CDirectionalLight::CDirectionalLight(const CDirectionalLight &other)
		: IUniformPack(other),
		ambient(other.ambient),
		diffuse(other.diffuse),
		specular(other.specular),
		direction(other.direction),
		color(other.color)
	{
		addUniform(ambient);
		addUniform(diffuse);
		addUniform(specular);
		addUniform(direction);
		addUniform(color);
	}

	std::unique_ptr<agl::IUniform> CDirectionalLight::clone() const
	{
		return std::unique_ptr<IUniform>(new CDirectionalLight(*this));
	}
}