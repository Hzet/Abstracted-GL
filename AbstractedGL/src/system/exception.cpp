#include "exception.hpp"
#include "error-code.hpp"

namespace agl
{
	namespace system
	{
		CException::CException(const std::string &message, error::EError code)
			: message_(message),
			code_(code)
		{
		}

		agl::error::EError CException::code() const
		{
			return code_;
		}

		char const* CException::what() const
		{
			return (message_ + " AGL error code [" + std::to_string(code_) + "] - " + getErrorMessage(code_)).c_str();
		}
	}
}

