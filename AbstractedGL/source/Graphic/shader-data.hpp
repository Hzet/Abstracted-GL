#pragma once
#include <string>

namespace agl
{
	class CShader;

	class IShaderData
	{
	public:
		IShaderData() = default;
		IShaderData(IShaderData&&) = default;
		IShaderData(const IShaderData&) = default;
		virtual ~IShaderData() = default;

		IShaderData& operator=(IShaderData&&) = default;
		IShaderData& operator=(const IShaderData&) = default;

		virtual std::unique_ptr<IShaderData> clone() const = 0;

	protected:
		friend class CShader;

		virtual void setData(const std::string &name, const CShader &shader) const = 0u;
	};
}