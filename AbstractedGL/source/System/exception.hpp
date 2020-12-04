#pragma once
#include <exception>
#include "log.hpp"

namespace agl
{
	namespace exception
	{
		struct CException
			: std::exception
		{
		public:
			explicit CException(const std::string &message);

			virtual char const* what() const override;
		};
	}
}
