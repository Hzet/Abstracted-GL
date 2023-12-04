#include "agl/debug/exceptions.hpp"

namespace agl
{
	exception::exception(const std::string &message) noexcept
		: m_message(message)
	{
	}

	exception::exception(const exception &other) noexcept
		: m_message(other.m_message)
	{
	}

	exception::exception(std::string &&message) noexcept
		: m_message(std::move(message))
	{
	}

	const char* exception::what() const noexcept
	{
		return m_message.c_str();
	}
}