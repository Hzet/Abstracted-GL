#pragma once

#include <string>
#include <unordered_map>

#include "shader-uid.hpp"
#include "shader-manager.hpp"

namespace agl
{
	/// <summary>
	/// A class that is a set of shader entries (uniforms) used by a particular entity.
	/// The user is ought to 'createEntry' on entity construction.
	/// The entry will be passed to a shader with 'shaderID' but it can be redirected to any other valid shader with a 'redirectEntry' method.
	/// </summary>
	class CShaderEntryManager
	{
	public:
		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CShaderEntryManager() = default;

		/// <summary>
		/// Defines an entry that the shader is capable of receiving.
		/// </summary>
		/// <param name="name">The entry's name</param>
		/// <param name="shaderID">The shader's unique identifier</param>
		void createEntry(const std::string &name, const CShaderUID &shaderUID);

		/// <summary>
		/// Redirects an entry so that it now will be passed to 'shaderID'.
		/// </summary>
		/// <param name="name">The entry's name</param>
		/// <param name="shaderID">The shader's unique identifier</param>
		void redirectEntry(const std::string &name, const CShaderUID &shaderUID);

		/// <summary>
		/// Passes a value with 'name' and 'value' to predefined destination. 
		/// Will fail if the entry of 'name' has not been yet defined in this particular instance.
		/// </summary>
		/// <param name="name">The entry's name</param>
		/// <param name="value">The entry's value</param>
		template <class T> void pass(const std::string &name, T value) const;

		void reset();

	private:
		std::unordered_map<std::string, CShaderUID> entries_;
	};

#include "shader-entry-manager.inl"
}