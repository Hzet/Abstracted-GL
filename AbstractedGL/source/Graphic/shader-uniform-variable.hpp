#pragma once

#include "shader-uniform.hpp"
#include "shader-uniform-manager.hpp"

namespace agl
{
	class IUniformVariable
		: public IUniform
	{
	public:
		/// <summary>
		/// Passes the uniform 'name' with 'value' to it's final destination.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="shaderUID">The unique identifier of the shader</param>
		template <class T> void passValue(const std::string &name, T value) const;

		/// <summary>
		/// Sets a new prefix 'name' for this uniform.
		/// </summary>
		/// <param name="name">The uniforms's name</param>
		virtual void setName(const std::string &name) override;

		/// <summary>
		/// Returns the shader's unique identifier that is assigned to uniform 'name'.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShaderOf(const std::string &name);

		/// <summary>
		/// Creates a new uniform with key 'name' assigned to shader represented as 'shaderUID'.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="shaderUID">The shader's unique identifier</param>
		void create(const std::string &name, const CShaderUID &shaderUID = CShaderUID::InvalidValue());

		/// <summary>
		/// Redirects the uniform 'name' in the CShaderEntryManager to be passed to 'shaderUID'.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="shaderUID">The unique identifier of the shader</param>
		void redirect(const std::string &name, const CShaderUID &shaderUID);

	private:
		/// <summary>
		/// Remove all the entries.
		/// </summary>
		void reset();

		CUniformManager uniformManager_;
	};

#include "shader-uniform-variable.inl"
}