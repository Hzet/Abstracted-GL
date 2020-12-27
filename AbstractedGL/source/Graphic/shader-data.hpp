#pragma once
#include <string>

namespace agl
{
	class CShader;

	/// <summary>
	/// Base interface to create custom shader data types which 
	/// are capable of sending themselves directly to the current shader program.
	/// </summary>
	class IShaderData
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		IShaderData() = default;

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		IShaderData(IShaderData&&) = default;

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		IShaderData(const IShaderData&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~IShaderData() = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		IShaderData& operator=(IShaderData&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		IShaderData& operator=(const IShaderData&) = default;

		/// <summary>
		/// Pure virtual clone method.
		/// </summary>
		/// <returns>
		/// Return the newly created copy of '*this'
		/// </returns>
		virtual std::unique_ptr<IShaderData> clone() const = 0;

	protected:
		friend class CShader;

		/// <summary>
		/// Invoke necessary uniform setters.
		/// </summary>
		/// <param name="name">Uniform name</param>
		/// <param name="shader">Shader program</param>
		virtual void setData(const std::string &name, const CShader &shader) const = 0u;
	};
}