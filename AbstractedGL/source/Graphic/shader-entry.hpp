#pragma once

#include "shader-entry-object.hpp"

namespace agl
{
	/// <summary>
	/// An interface to provide easy to use setters for compound shader uniforms. 
	/// </summary>
	class IShaderEntry
		: private CShaderEntryManager
	{
	public:
		/// <summary>
		/// Returns the name (prefix) of the entry.
		/// </summary>
		/// <returns>The prefix</returns>
		const std::string& getName() const;

		/// <summary>
		/// Sets the name (prefix) of the compound type.
		/// </summary>
		/// <param name="name">The prefix</param>
		virtual void setName(const std::string &name);

		/// <summary>
		/// Registers the entry 'name' in the CshaderEntryManager to be passed to 'shaderUID'.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="shaderUID">The unique identifier of the shader</param>
		void attachEntry(const std::string &name, const CShaderUID &shaderUID);

		/// <summary>
		/// Redirects the entry 'name' in the CShaderEntryManager to be passed to 'shaderUID'.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="shaderUID">The unique identifier of the shader</param>
		void redirectEntry(const std::string &name, const CShaderUID &shaderUID);

		/// <summary>
		/// Passes the entry 'name' with 'value' to it's final destination.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="shaderUID">The unique identifier of the shader</param>
		template <class T> void passEntry(const std::string &name, T value) const;

		/// <summary>
		/// A pure virtual method to pass individual sub entries of the compound type.
		/// </summary>
		virtual void passToShader() const = 0;

		/// <summary>
		/// Create a polymorphic copy of this entry.
		/// </summary>
		/// <returns>The copy</returns>
		virtual std::unique_ptr<IShaderEntry> clone() const = 0;

	private:
		std::string name_;
	};

#include "shader-entry.inl"
}