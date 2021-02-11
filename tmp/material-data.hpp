#pragma once

#include "shader-data.hpp"

#include <glm/glm.hpp>

namespace agl
{
	class CMaterial final
		: public IShaderData
	{
	public:
		CMaterial() = default;
		CMaterial(CMaterial&&) = default;
		CMaterial(const CMaterial&) = default;
		CMaterial(const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const float shininess);

		CMaterial& operator=(CMaterial&&) = default;
		CMaterial& operator=(const CMaterial&) = default;

		float shininess;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

	private:
		virtual void setData(const std::string &name, const CShader &shader) const override;

		virtual std::unique_ptr<IShaderData> clone() const override;
	};

	namespace Material
	{
		const CMaterial Emerald		  = CMaterial({ 0.021500f, 0.174500f, 0.021500f, 1.f }, { 0.075680f, 0.614240f, 0.075680f, 1.f }, { 0.633000f, 0.727811f, 0.633000f, 1.f }, 0.600000f);
		const CMaterial Jade		  = CMaterial({ 0.135000f, 0.222500f, 0.157500f, 1.f }, { 0.540000f, 0.890000f, 0.630000f, 1.f }, { 0.316228f, 0.316228f, 0.316228f, 1.f }, 0.100000f);
		const CMaterial Obsidian	  = CMaterial({ 0.053750f, 0.050000f, 0.066250f, 1.f }, { 0.182750f, 0.170000f, 0.225250f, 1.f }, { 0.332741f, 0.328634f, 0.346435f, 1.f }, 0.300000f);
		const CMaterial Pearl		  = CMaterial({ 0.250000f, 0.207250f, 0.207250f, 1.f }, { 1.000000f, 0.829000f, 0.829000f, 1.f }, { 0.296648f, 0.296648f, 0.296648f, 1.f }, 0.088000f);
		const CMaterial Ruby		  = CMaterial({ 0.174500f, 0.011750f, 0.011750f, 1.f }, { 0.614240f, 0.041360f, 0.041360f, 1.f }, { 0.727811f, 0.626959f, 0.626959f, 1.f }, 0.600000f);
		const CMaterial Turquoise	  = CMaterial({ 0.100000f, 0.187250f, 0.174500f, 1.f }, { 0.396000f, 0.741510f, 0.691020f, 1.f }, { 0.297254f, 0.308290f, 0.306678f, 1.f }, 0.100000f);
		const CMaterial Brass		  = CMaterial({ 0.329412f, 0.223529f, 0.027451f, 1.f }, { 0.780392f, 0.568627f, 0.113725f, 1.f }, { 0.992157f, 0.941176f, 0.807843f, 1.f }, 0.217949f);
		const CMaterial Bronze		  = CMaterial({ 0.212500f, 0.127500f, 0.054000f, 1.f }, { 0.714000f, 0.428400f, 0.181440f, 1.f }, { 0.393548f, 0.271906f, 0.166721f, 1.f }, 0.200000f);
		const CMaterial Chrome		  = CMaterial({ 0.250000f, 0.250000f, 0.250000f, 1.f }, { 0.400000f, 0.400000f, 0.400000f, 1.f }, { 0.774597f, 0.774597f, 0.774597f, 1.f }, 0.600000f);
		const CMaterial Copper		  = CMaterial({ 0.191250f, 0.073500f, 0.022500f, 1.f }, { 0.703800f, 0.270480f, 0.082800f, 1.f }, { 0.256777f, 0.137622f, 0.086014f, 1.f }, 0.100000f);
		const CMaterial Gold		  = CMaterial({ 0.247250f, 0.199500f, 0.074500f, 1.f }, { 0.751640f, 0.606480f, 0.226480f, 1.f }, { 0.628281f, 0.555802f, 0.366065f, 1.f }, 0.400000f);
		const CMaterial Silver		  = CMaterial({ 0.192250f, 0.192250f, 0.192250f, 1.f }, { 0.507540f, 0.507540f, 0.507540f, 1.f }, { 0.508273f, 0.508273f, 0.508273f, 1.f }, 0.400000f);
		const CMaterial BlackPlastic  = CMaterial({ 0.000000f, 0.000000f, 0.000000f, 1.f }, { 0.010000f, 0.010000f, 0.010000f, 1.f }, { 0.500000f, 0.500000f, 0.500000f, 1.f }, 0.250000f);
		const CMaterial CyanPlastic	  = CMaterial({ 0.000000f, 0.100000f, 0.060000f, 1.f }, { 0.000000f, 0.509804f, 0.509804f, 1.f }, { 0.501961f, 0.501961f, 0.501961f, 1.f }, 0.250000f);
		const CMaterial GreenPlastic  = CMaterial({ 0.000000f, 0.000000f, 0.000000f, 1.f }, { 0.100000f, 0.350000f, 0.100000f, 1.f }, { 0.450000f, 0.550000f, 0.450000f, 1.f }, 0.250000f);
		const CMaterial RedPlastic	  = CMaterial({ 0.000000f, 0.000000f, 0.000000f, 1.f }, { 0.500000f, 0.000000f, 0.000000f, 1.f }, { 0.700000f, 0.600000f, 0.600000f, 1.f }, 0.250000f);
		const CMaterial WhitePlastic  = CMaterial({ 0.000000f, 0.000000f, 0.000000f, 1.f }, { 0.550000f, 0.550000f, 0.550000f, 1.f }, { 0.700000f, 0.700000f, 0.700000f, 1.f }, 0.250000f);
		const CMaterial YellowPlastic = CMaterial({ 0.000000f, 0.000000f, 0.000000f, 1.f }, { 0.500000f, 0.500000f, 0.000000f, 1.f }, { 0.600000f, 0.600000f, 0.500000f, 1.f }, 0.250000f);
		const CMaterial BlackRubber	  = CMaterial({ 0.020000f, 0.020000f, 0.020000f, 1.f }, { 0.010000f, 0.010000f, 0.010000f, 1.f }, { 0.400000f, 0.400000f, 0.400000f, 1.f }, 0.078125f);
		const CMaterial CyanRubber	  = CMaterial({ 0.000000f, 0.050000f, 0.050000f, 1.f }, { 0.400000f, 0.500000f, 0.500000f, 1.f }, { 0.040000f, 0.700000f, 0.700000f, 1.f }, 0.078125f);
		const CMaterial GreenRubber	  = CMaterial({ 0.000000f, 0.050000f, 0.000000f, 1.f }, { 0.400000f, 0.500000f, 0.400000f, 1.f }, { 0.040000f, 0.700000f, 0.040000f, 1.f }, 0.078125f);
		const CMaterial RedRubber	  = CMaterial({ 0.050000f, 0.000000f, 0.000000f, 1.f }, { 0.500000f, 0.400000f, 0.400000f, 1.f }, { 0.700000f, 0.040000f, 0.040000f, 1.f }, 0.078125f);
		const CMaterial WhiteRubber   = CMaterial({ 0.050000f, 0.050000f, 0.050000f, 1.f }, { 0.500000f, 0.500000f, 0.500000f, 1.f }, { 0.700000f, 0.700000f, 0.700000f, 1.f }, 0.078125f);
		const CMaterial YellowRubber  = CMaterial({ 0.050000f, 0.050000f, 0.000000f, 1.f }, { 0.500000f, 0.500000f, 0.400000f, 1.f }, { 0.700000f, 0.700000f, 0.040000f, 1.f }, 0.078125f);
	}
}