#pragma once

#include "shader-uniform.hpp"
#include "shader-manager.hpp"
#include "shader-uid.hpp"

#include <iomanip>

namespace agl
{
	namespace detail
	{
		/// <summary>
		/// A helper value placeholder struct.
		/// </summary>
		template <typename T>
		struct TValue
		{
			T value;
		};

		/// <summary>
		/// Deduces if the type T is a class.
		/// </summary>
		template <typename T>
		using is_class_t = std::enable_if_t<std::is_class_v<std::remove_reference_t<T>>>;

		/// <summary>
		/// Deduces if the type T is a pointer to a function.
		/// </summary>
		template <typename T>
		using is_function_pointer_t = std::enable_if_t<std::is_function_v<std::remove_pointer_t<T>>>;

		/// <summary>
		/// Combines the 'is_class_t' and 'is_function_pointer_t' typedefs.
		/// </summary>
		template <typename TObject, typename TMethod>
		using is_class_method = std::enable_if_t<std::is_class_v<std::remove_reference_t<TObject>> && std::is_member_function_pointer_v<std::remove_reference_t<TMethod>>>;

		/// <summary>
		/// A declaration of a type to specialize.
		/// </summary>
		template <typename TReturn, typename TObject, typename = void>
		struct method_pointer
		{
		};

		/// <summary>
		/// 'type' is a const method type belonging to class 'TObject' and returning 'TReturn'.
		/// </summary>
		template <typename TReturn, typename TObject>
		struct method_pointer<TReturn, TObject, typename std::enable_if<std::is_const<typename std::remove_reference<TObject>::type>::value>::type>
		{
			using type = TReturn(std::remove_reference<TObject>::type::*)() const;
		};

		/// <summary>
		/// 'type' is a method type belonging to class 'TObject' and returning 'TReturn'.
		/// </summary>
		template <typename TReturn, typename TObject>
		struct method_pointer<TReturn, TObject, typename std::enable_if<!std::is_const<typename std::remove_reference<TObject>::type>::value>::type>
		{
			using type = TReturn(std::remove_reference<TObject>::type::*)();
		};

		/// <summary>
		/// A helper typedef.
		/// </summary>
		template <typename TReturn, typename TObject>
		using method_pointer_t = typename method_pointer<TReturn, TObject>::type;
	}



	/// <summary>
	/// Declaration of a class to be specialized.
	/// </summary>
	template <typename, typename = void, typename = void, typename = void>
	class CUniform
	{
	};



	/// <summary>
	/// Uniform variable that contains a variable of type 'TReturn'.
	/// </summary>
	template <typename TReturn>
	class CUniform<TReturn>
		: public IUniform
	{
	public:
		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' to contain 'value' and be passed to 'shaderUID'.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="value">The value</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		CUniform(const std::string &name, IUniform const * const parent = nullptr, detail::TValue<TReturn> &&value = {}, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});
		
		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(CUniform &&other);

		/// <summary>
		/// Copy constructor. Is disabled for non assignable classes.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(const CUniform &other);

		/// <summary>
		/// Copy constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="value">The value</param>
		CUniform(const CUniform &other, detail::TValue<TReturn> &&value, IUniform const * const parent = nullptr);

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(CUniform&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(const CUniform&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CUniform() = default;

		/// <summary>
		/// Returns the uniform destination shader.
		/// </summary>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShader() const;

		/// <summary>
		/// Sets the uniform destination shader.
		/// </summary>
		/// <param name="shaderUID">The shader's unique identifier</param>
		virtual void setShader(const CShaderUID &shaderUID) override;

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		TType& operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		const auto& operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator auto&();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator const auto&() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

	private:
		TReturn value_;
		CShaderUID shaderUID_;
	};


	/// <summary>
	/// Uniform that it's value must be updated every time it's retrieved.
	/// The retrieve of the value is done by a method returning type 'TReturn' belonging to object 'TObject'.
	/// </summary>
	template <typename TReturn, typename TObject>
	class CUniform<TReturn, TObject, detail::is_class_t<TObject>>
		: public IUniform
	{
		using TMethod = detail::method_pointer_t<TReturn, TObject>;

	public:
		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' to retrieve the value of type 'TReturn' from an 'object' with a 'method' and be send to 'shaderUID'
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="object">An object on which the 'method' will be called</param>
		/// <param name="method">An address of a method that will be called on an 'object'</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		CUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent = nullptr, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});
		
		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(CUniform &&other);

		/// <summary>
		/// Copy constructor. Is disabled for non assignable classes.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(const CUniform &other);

		/// <summary>
		/// Copy constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="object">The object on which the method will be called</param>
		CUniform(const CUniform &other, detail::TValue<TObject> &&object, IUniform const * const parent = nullptr);
		
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(CUniform&&) = default;

		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(const CUniform&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CUniform() = default;

		/// <summary>
		/// Returns the uniform destination shader.
		/// </summary>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShader() const;

		/// <summary>
		/// Sets the uniform destination shader.
		/// </summary>
		/// <param name="shaderUID">The shader's unique identifier</param>
		virtual void setShader(const CShaderUID &shaderUID) override;

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		auto& operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		const auto& operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator auto&();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator const auto&() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

	private:
		TObject object_;
		TMethod method_;
		CShaderUID shaderUID_;
	};



	/// <summary>
	/// Uniform that must be updated every time it's retrieved.
	/// The function which is used to return updated value is of 'TFunction' type.
	/// The value returned by that function is of 'TReturn' type.
	/// </summary>
	template <typename TReturn, typename TFunction>
	class CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>
		: public IUniform
	{
	public:
		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' retrieved with the 'function'.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="method">An address of a function that will be called to retrieve the value</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		CUniform(const std::string &name, detail::TValue<TFunction> &&function, IUniform const * const parent = nullptr, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(CUniform &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(const CUniform &other);

		/// <summary>
		/// Copy constructor with the scope change.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		CUniform(const CUniform &other, IUniform const * const parent);

		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(CUniform&&) = default;
		
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(const CUniform&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CUniform() = default;

		/// <summary>
		/// Returns the uniform destination shader.
		/// </summary>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShader() const;

		/// <summary>
		/// Sets the uniform destination shader.
		/// </summary>
		/// <param name="shaderUID">The shader's unique identifier</param>
		virtual void setShader(const CShaderUID &shaderUID) override;

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		auto& operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		const auto& operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator auto&();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator const auto&() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

	private:
		TFunction function_;
		CShaderUID shaderUID_;
	};


	/// <summary>
	/// Uniform that it's value must be updated every time it's retrieved.
	/// The retrieve of the value is done by a method of type 'TMethod'.
	/// The method return value of 'TReturn' type and is called on object of type 'TObject'.
	/// </summary>
	template <typename TReturn, typename TObject, typename TMethod>
	class CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>
		: public IUniform
	{
	public:
		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' to retrieve the value of type 'TReturn' from an 'object' with a 'method' and be send to 'shaderUID'
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="object">An object on which the 'method' will be called</param>
		/// <param name="method">An address of a method that will be called on an 'object'</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		CUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent = nullptr, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(CUniform &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CUniform(const CUniform &other);

		/// <summary>
		/// Copy constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="object">The object on which the method will be called</param>
		CUniform(const CUniform &other, detail::TValue<TObject> &&object, IUniform const * const parent = nullptr);

		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(CUniform&&) = default;

		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CUniform& operator=(const CUniform&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CUniform() = default;

		/// <summary>
		/// Returns the uniform destination shader.
		/// </summary>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShader() const;

		/// <summary>
		/// Sets the uniform destination shader.
		/// </summary>
		/// <param name="shaderUID">The shader's unique identifier</param>
		virtual void setShader(const CShaderUID &shaderUID) override;

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		auto& operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		const auto& operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator auto&();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator const auto&() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

	private:
		TObject object_;
		TMethod method_;
		CShaderUID shaderUID_;
	};

#include "shader-uniform-variable.inl"
}