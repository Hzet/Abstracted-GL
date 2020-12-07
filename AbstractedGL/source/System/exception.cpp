#include "exception.hpp"

namespace agl
{
	namespace exception
	{
		CException::CException(const std::string &message)
			: message_(message)
		{
		}

		char const* CException::what() const
		{
			return message_.c_str();
		}
	}
}

