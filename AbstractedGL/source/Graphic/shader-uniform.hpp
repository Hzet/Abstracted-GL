#pragma once
#include <memory>
#include <vector>

#include "shader-uid.hpp"
#include "../System/inheritable-vector.hpp"

namespace agl
{
	/// <summary>
	/// An interface for uniforms. 
	/// Each uniforms can be described by common features it has:
	///  > name - name of the uniform
	///  > fullname - the scope, in which the uniform is created, concatenated with it's name
	///  > destination shader - an unique identifier of the shader, to which the value of the uniform will be passed
	///  > (optional) index - an index of the uniform in array
	/// 
	/// There are two ways of creating a copy of the uniform: 
	///  1. single parameter copy constructor - copies the name and the scope of the uniform
	///  2. two parameter copy constructor - copies the name and change the scope to be in 'parent's namespace
	/// </summary>
	class IUniform
	{
	public:
		/// <summary>
		/// Creates the uniform with 'name' in 'parent's scope.
		/// </summary>
		/// <param name="name">The uniform's name</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		IUniform(const std::string &name, IUniform const * const parent = nullptr);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		IUniform(IUniform &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		IUniform(const IUniform &other);

		/// <summary>
		/// Copy constructor with the scope change.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		IUniform(const IUniform &other, IUniform const * const parent);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~IUniform() = default;

		/// <summary>
		/// Returns the name of the uniform.
		/// </summary>
		/// <returns>The name</returns>
		const std::string& getName() const;

		/// <summary>
		/// Returns the scope and the name of the instance.
		/// </summary>
		/// <returns></returns>
		const std::string& getFullName() const;

		/// <summary>
		/// Passes the uniform to shader.
		/// </summary>
		virtual void passUniform() const = 0;

		/// <summary>
		/// Inserts the 'index' in square brackets into the uniform's name.
		/// </summary>
		/// <param name="index">The index</param>
		virtual void setIndex(std::uint64_t index);

		/// <summary>
		/// Set destination 'shaderUID'.
		/// </summary>
		/// <param name="shaderUID">The destination shader unique identifier</param>
		virtual void setShader(const CShaderUID &shaderUID) = 0;

	//protected:
		/// <summary>
		/// Change the namespace of the uniform.
		/// </summary>
		/// <param name="name"></param>
		virtual void updateNamespace(const std::string &name);

	private:
		/// <summary>
		/// Helper method to set the fullname of the instance.
		/// </summary>
		/// <param name="fullname"></param>
		void setFullName(const std::string &fullname);

		std::string name_;
		std::string fullname_;
	};
}