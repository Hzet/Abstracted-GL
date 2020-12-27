#pragma once
#include <string>
#include <exception>

namespace agl
{
	namespace Error
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
			explicit CException(const std::string &message, Error::EError code);

			/// <summary>
			/// Get the error code.
			/// </summary>
			/// <returns>
			/// The error code
			/// </returns>
			Error::EError code() const;

			/// <summary>
			/// Get the error message.
			/// </summary>
			/// <returns>
			/// The error message
			/// </returns>
			virtual char const* what() const override;

		private:
			Error::EError code_;	
			const std::string message_;
		};
	}
}
