#pragma once

#include "shader-uniform.hpp"
#include "shader-manager.hpp"
#include "shader-uid.hpp"


#include <type_traits>
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
		using is_class_method = std::enable_if_t<std::is_class_v<std::remove_reference_t<TObject>> 
												 && std::is_member_function_pointer_v<std::remove_reference_t<TMethod>>>;

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
		struct method_pointer<TReturn, TObject, std::enable_if_t<std::is_const_v<std::remove_reference_t<TObject>>>>
		{
			using type = TReturn(std::remove_reference<TObject>::type::*)() const;
		};

		/// <summary>
		/// 'type' is a method type belonging to class 'TObject' and returning 'TReturn'.
		/// </summary>
		template <typename TReturn, typename TObject>
		struct method_pointer<TReturn, TObject, std::enable_if_t<!std::is_const_v<std::remove_reference_t<TObject>>>>
		{
			using type = TReturn(std::remove_reference<TObject>::type::*)();
		};

		/// <summary>
		/// A helper typedef.
		/// </summary>
		template <typename TReturn, typename TObject>
		using method_pointer_t = typename method_pointer<TReturn, TObject>::type;

		template <typename T>
		using true_type_t = std::remove_reference_t<T>;
	}

	/// <summary>
	/// Declaration of a class to be specialized.
	/// </summary>
	template <typename, typename = void, typename = void, typename = void>
	class TUniform
	{
	};

	/// <summary>
	/// Uniform variable that contains a variable of type 'TReturn'.
	/// </summary>
	template <typename TReturn>
	class TUniform<TReturn>
		: public IUniform
	{
		using TType = std::conditional_t<std::is_reference_v<TReturn>, std::reference_wrapper<std::remove_reference_t<TReturn>>, TReturn>;
	public:
		using IUniform::IUniform;

		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' to contain 'value' and be passed to 'shaderUID'.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="value">The value</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		TUniform(const std::string &name, IUniform const * const parent = nullptr, detail::TValue<TReturn> &&value = {}, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});

		/// <summary>
		/// Move constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="value">The value</param>
		TUniform(TUniform &&other, detail::TValue<TReturn> &&value);

		/// <summary>
		/// Copy constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="value">The value</param>
		TUniform(const TUniform &other, detail::TValue<TReturn> &&value);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~TUniform() = default;

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
		detail::true_type_t<TReturn>& operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		const detail::true_type_t<TReturn>& operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator detail::true_type_t<TReturn>&();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator const detail::true_type_t<TReturn>&() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;
		
		/// <summary>
		/// Returns a copy of this uniform in a unique_ptr wrapper.
		/// </summary>
		/// <returns>The unique pointer</returns>
		virtual std::unique_ptr<IUniform> clone() const override;

	private:
		TType value_;
		CShaderUID shaderUID_;
	};


	/// <summary>
	/// Uniform that it's value must be updated every time it's retrieved.
	/// The retrieve of the value is done by a method returning type 'TReturn' belonging to object 'TObject'.
	/// </summary>
	template <typename TReturn, typename TObject>
	class TUniform<TReturn, TObject, detail::is_class_t<TObject>>
		: public IUniform
	{
		using TMethod = detail::method_pointer_t<TReturn, TObject>;

	public:
		using IUniform::IUniform;

		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' to retrieve the value of type 'TReturn' from an 'object' with a 'method' and be send to 'shaderUID'
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="object">An object on which the 'method' will be called</param>
		/// <param name="method">An address of a method that will be called on an 'object'</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		TUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent = nullptr, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});

		/// <summary>
		/// Move constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="object">The object on which the method will be called</param>
		TUniform(TUniform &&other, detail::TValue<TObject> &&object);

		/// <summary>
		/// Copy constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="object">The object on which the method will be called</param>
		TUniform(const TUniform &other, detail::TValue<TObject> &&object);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~TUniform() = default;

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
		TReturn operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		TReturn operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator TReturn();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator TReturn() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

		/// <summary>
		/// Returns a copy of this uniform in a unique_ptr wrapper.
		/// </summary>
		/// <returns>The unique pointer</returns>
		virtual std::unique_ptr<IUniform> clone() const override;

	private:
		std::reference_wrapper<std::remove_reference_t<TObject>> object_;
		TMethod method_;
		CShaderUID shaderUID_;
	};

	/// <summary>
	/// Uniform that it's value must be updated every time it's retrieved.
	/// The retrieve of the value is done by a method of type 'TMethod'.
	/// The method return value of 'TReturn' type and is called on object of type 'TObject'.
	/// </summary>
	template <typename TReturn, typename TObject, typename TMethod>
	class TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>
		: public IUniform
	{
	public:
		using IUniform::IUniform;

		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' to retrieve the value of type 'TReturn' from an 'object' with a 'method' and be send to 'shaderUID'
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="object">An object on which the 'method' will be called</param>
		/// <param name="method">An address of a method that will be called on an 'object'</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		TUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent = nullptr, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});

		/// <summary>
		/// Move constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="object">The object on which the method will be called</param>
		TUniform(TUniform &&other, detail::TValue<TObject> &&object);

		/// <summary>
		/// Copy constructor with the scope change.
		/// Can be used for reference types.
		/// </summary>
		/// <param name="other">The other instance</param>
		/// <param name="object">The object on which the method will be called</param>
		TUniform(const TUniform &other, detail::TValue<TObject> &&object);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~TUniform() = default;

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
		TReturn operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		TReturn operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator TReturn();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator TReturn() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

		/// <summary>
		/// Returns a copy of this uniform in a unique_ptr wrapper.
		/// </summary>
		/// <returns>The unique pointer</returns>
		virtual std::unique_ptr<IUniform> clone() const override;

	private:
		std::reference_wrapper<std::remove_reference_t<TObject>> object_;
		TMethod method_;
		CShaderUID shaderUID_;
	};

	/// <summary>
	/// Uniform that must be updated every time it's retrieved.
	/// The function which is used to return updated value is of 'TFunction' type.
	/// The value returned by that function is of 'TReturn' type.
	/// </summary>
	template <typename TReturn, typename TFunction>
	class TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>
		: public IUniform
	{
	public:
		using IUniform::IUniform;

		/// <summary>
		/// Constructs a uniform with 'name', namespace of 'parent' retrieved with the 'function'.
		/// </summary>
		/// <param name="name">The name of the uniform</param>
		/// <param name="parent">The parent which aggregates this uniform</param>
		/// <param name="method">An address of a function that will be called to retrieve the value</param>
		/// <param name="shaderUID">the shader's unique identifier</param>
		TUniform(const std::string &name, detail::TValue<TFunction> &&function, IUniform const * const parent = nullptr, const CShaderUID &shaderUID = CShaderUID::InvalidValue{});

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~TUniform() = default;

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
		TReturn operator()();

		/// <summary>
		/// Returns the value.
		/// </summary>
		/// <returns>The value</returns>
		TReturn operator()() const;

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator TReturn();

		/// <summary>
		/// Cast operator to value type the 'TReturn'.
		/// </summary>
		/// <returns>The value</returns>
		operator TReturn() const;

		/// <summary>
		/// Passes the uniform to it's shader.
		/// </summary>
		virtual void passUniform() const override;

		/// <summary>
		/// Returns a copy of this uniform in a unique_ptr wrapper.
		/// </summary>
		/// <returns>The unique pointer</returns>
		virtual std::unique_ptr<IUniform> clone() const override;

	private:
		TFunction function_;
		CShaderUID shaderUID_;
	};

#include "shader-uniform-variable.inl"
}