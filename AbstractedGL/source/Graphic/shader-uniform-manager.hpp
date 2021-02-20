#pragma once

#include <string>
#include <unordered_map>

#include "shader-uid.hpp"
#include "shader-manager.hpp"

namespace agl
{
	class IUniform;

	/// <summary>
	/// A class that is a set of shader entries (uniforms) used by a particular entity.
	/// The user is ought to 'createEntry' on entity construction.
	/// The uniform will be passed to a shader with 'shaderID' but it can be redirected to any other valid shader with a 'redirectEntry' method.
	/// </summary>
	class CUniformManager
	{
	public:
		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CUniformManager() = default;

		/// <summary>
		/// Defines an uniform that the shader is capable of receiving.
		/// </summary>
		/// <param name="name">The uniform's name</param>
		/// <param name="shaderID">The shader's unique identifier</param>
		void create(const std::string &name, const CShaderUID &shaderUID);

		/// <summary>
		/// Redirects an uniform so that it now will be passed to 'shaderID'.
		/// </summary>
		/// <param name="name">The uniform's name</param>
		/// <param name="shaderID">The shader's unique identifier</param>
		void redirect(const std::string &name, const CShaderUID &shaderUID);

		/// <summary>
		/// Returns the unique identifier that is assigned to the uniform with 'name'.
		/// </summary>
		/// <param name="name">The uniform's name</param>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShaderOf(const std::string &name) const;

		/// <summary>
		/// Passes a value with 'name' and 'value' to predefined destination. 
		/// Will fail if the uniform of 'name' has not been yet defined in this particular instance.
		/// </summary>
		/// <param name="name">The uniform's name</param>
		/// <param name="value">The uniform's value</param>
		template <class T> void pass(const std::string &name, T value) const;

		/// <summary>
		/// Removes all entries from current set.
		/// </summary>
		void reset();

		/// <summary>
		/// Returns an unordered map of entries.
		/// </summary>
		/// <returns>The entries</returns>
		const std::unordered_map<std::string, CShaderUID>& getEntries() const;

	private:
		std::unordered_map<std::string, CShaderUID> entries_;
	};

#include "shader-uniform-manager.inl"
}