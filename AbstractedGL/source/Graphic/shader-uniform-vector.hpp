#pragma once 

#include <vector>

#include "shader-uniform.hpp"
#include "../System/inheritable-vector.hpp"

namespace agl
{
	/// <summary>
	/// A wrapper around std::vector<> of unique pointers of IShaderEntryPack so the other classes can inherit from it,
	/// avoiding the need to provide implementation of it's features.
	/// </summary>
	class CUniformVector
		: public system::CInheritableVector<std::unique_ptr<IUniform>>
	{
	public:
		using system::CInheritableVector<std::unique_ptr<IUniform>>::CInheritableVector;

		/// <summary>
		/// Default constructor.
		/// </summary>
		CUniformVector() = default;

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CUniformVector(CUniformVector&&) = default;

		/// <summary>
		/// Deep copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniformVector(const CUniformVector &other);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CUniformVector() = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniformVector& operator=(CUniformVector&&) = default;

		/// <summary>
		/// Deep copy assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>The reference to this</returns>
		CUniformVector& operator=(const CUniformVector &other);

		/// <summary>
		/// Passes the contained shader's entries to it's destination shaders.
		/// </summary>
		void passToShader() const;
	};
}