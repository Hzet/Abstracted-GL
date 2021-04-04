#pragma once
#include <string>
#include <exception>

namespace agl
{
	namespace error
	{
		enum EError : std::uint64_t;
	}
	namespace system
	{
		/// <summary>
		/// Custom exception class that is provided with a message and the AGL error code.
		/// </summary>
		class CException
			: virtual public std::exception
		{
		public:
			/// <summary>
			/// Full constructor.
			/// </summary>
			/// <param name="message">The message</param>
			/// <param name="code">The AGL error code</param>
			explicit CException(const std::string &message, error::EError code);

			/// <summary>
			/// Get the error code.
			/// </summary>
			/// <returns>
			/// The error code
			/// </returns>
			error::EError code() const;

			/// <summary>
			/// Get the error message.
			/// </summary>
			/// <returns>
			/// The error message
			/// </returns>
			virtual char const* what() const override;

		private:
			error::EError code_;	
			const std::string message_;
		};
	}
}
