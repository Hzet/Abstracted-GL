#pragma once
#include <string>
#include <exception>

namespace agl
{
	namespace exception
	{
		class CException
			: public std::exception
		{
		public:
			explicit CException(const std::string &message);

			virtual char const* what() const override;

		private:
			const std::string message_;
		};
	}
}
