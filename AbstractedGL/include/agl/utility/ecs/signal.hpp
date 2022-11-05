#pragma once

namespace agl
{
	/// <summary>
	/// A wrapper around the signal.
	/// </summary>
	template <typename T>
	class signal
	{
	public:
		/// <summary>
		/// Defaulted constructor.
		/// </summary>
		signal() = default;

		/// <summary>
		/// value initialization constructor.
		/// Initializes the value with 'args'.
		/// </summary>
		/// <param name="...args">The initialization arguments</param>
		template <typename... Args>	signal(Args&&... args);
		
		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object.</param>
		signal(signal &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		signal(const signal &other);
		
		/// <summary>
		/// Move assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>The reference to *this</returns>
		signal& operator=(signal &&other);

		/// <summary>
		/// Copy assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>The reference to *this</returns>
		signal& operator=(const signal &other);

		/// <summary>
		/// Move assigns the 'value' to the value stored by this signal.
		/// </summary>
		/// <param name="value">The value</param>
		/// <returns>The reference to *this</returns>
		template <typename U>
		signal& operator=(U &&value);

		/// <summary>
		/// copy assigns the 'value' to the value stored by this signal.
		/// </summary>
		/// <param name="value">The value</param>
		/// <returns>The reference to *this</returns>
		template <typename U> 
		signal& operator=(const U &value);

		/// <summary>
		/// Implicit cast operator to stored value.
		/// </summary>
		/// <returns>The stored value</returns>
		operator T&();

		/// <summary>
		/// Implicit cast operator to stored value.
		/// </summary>
		/// <returns>The stored value</returns>
		operator T&() const;

		/// <summary>
		/// Returns a reference to the stored value.
		/// </summary>
		/// <returns>The reference</returns>
		T& get();

		/// <summary>
		/// Returns a reference to the stored value.
		/// </summary>
		/// <returns>The reference</returns>
		const T& get() const;

	private:

		T m_data;
	};

#include "agl/utility/ecs/signal.inl"
}