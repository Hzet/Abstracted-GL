#pragma once

#include <type_traits>

#include "shader-uniform.hpp"
#include "../System/inheritable-vector.hpp"

namespace agl
{
	namespace detail
	{
		/// <summary>
		/// Check whether the type T is an AGL uniform.
		/// </summary>
		template <typename T>
		struct is_agl_uniform
			: std::enable_if<std::is_base_of<IUniform, T>::value &&
			!std::is_same<IUniform, T>::value &&
			!std::is_same<IUniformPack, T>::value>
		{
		};

		/// <summary>
		/// Helper typedef.
		/// </summary>
		template <typename T>
		using is_agl_uniform_t = typename is_agl_uniform<T>::type;
	}

	/// <summary>
	/// A declaration of the array of the uniforms.
	/// </summary>
	template <typename T, typename = void>
	class CUniformArray
	{
	};

	/// <summary>
	/// An array that accepts only IUniform and IUniformPack derived classes excluding the mentioned earlier base classes.
	/// The elements of the array will automatically update theirs indexes if the count of the elements change.
	/// The array itself is an uniform and the appropriate interface is implemented within it.
	/// </summary>
	template <typename T>
	class CUniformArray<T, detail::is_agl_uniform_t<T>>
		: public IUniform,
		public system::CInheritableVector<T>
	{
	public:
		/// <summary>
		/// Creates the uniform with 'name' in 'parent's scope.
		/// </summary>
		/// <param name="name">The uniform's name</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		CUniformArray(const std::string &name, IUniform const * const parent = nullptr);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniformArray(CUniformArray &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniformArray(const CUniformArray &other);

		/// <summary>
		/// Copy constructor with the scope change.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		CUniformArray(const CUniformArray &other, IUniform const * const parent);

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniformArray& operator=(CUniformArray&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniformArray& operator=(const CUniformArray&) = default;

		/// <summary>
		/// Passes all of the uniforms to it's shaders.
		/// </summary>
		virtual void passUniform() const override;

		/// <summary>
		/// Sets the index of this array instance and updates the scopes of contained uniforms.
		/// </summary>
		/// <param name="index">The index</param>
		virtual void setIndex(std::uint64_t index) override;

		/// <summary>
		/// Set all uniforms to be send to the shader assigned to 'shaderUID'.
		/// </summary>
		/// <param name="shaderUID">The shaderUID</param>
		virtual void setShader(const CShaderUID &shaderUID) override;

	private:
		/// <summary>
		/// Helper method. Updates the namespace of this and contained uniforms.
		/// </summary>
		/// <param name="name">new namespace</param>
		virtual void updateNamespace(const std::string &name) override;

		std::uint64_t lastCount_;
	};

#include "shader-uniform-array.inl"
}