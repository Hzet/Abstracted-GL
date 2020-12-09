#include "exception.hpp"
#include "core-error-codes.hpp"

namespace agl
{
	namespace exception
	{
		CException::CException(const std::string &message, Error::EError code)
			: message_(message),
			code_(code)
		{
		}

		agl::Error::EError CException::code() const
		{
			return code_;
		}

		char const* CException::what() const
		{
			return (message_ + " AGL error code [" + std::to_string(code_) + "] - " + getErrorMessage(code_)).c_str();
		}
	}
}

