#pragma once 

#include "shader-uniform-variable.hpp"

namespace agl
{
	/// <summary>
	/// A wrapper around CShaderEntryManager so the other classes can inherit from it,
	/// avoiding the need to provide implementation of it's features.
	/// </summary>
	class CUniformObject
	{
	public:
		/// <summary>
		/// Redirects an 'name' entry to be now passed to 'shaderUID' shader.
		/// </summary>
		/// <param name="name">The entry's name</param>
		/// <param name="shaderUID">The shader's unique identifier</param>
		void redirectEntry(const std::string &name, const CShaderUID &shaderUID);

		const CUniformManager& get() const;

	protected:
		CUniformManager entryManager_;
	};
}