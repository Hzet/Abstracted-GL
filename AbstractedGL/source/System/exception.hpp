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
		class CException
			: virtual public std::exception
		{
		public:
			explicit CException(const std::string &message, Error::EError code);

			Error::EError code() const;
			virtual char const* what() const override;

		private:
			Error::EError code_;	
			const std::string message_;
		};
	}
}
