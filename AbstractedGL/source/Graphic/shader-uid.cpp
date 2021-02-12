/*
#include "shader-uid.hpp"

#include <iostream>

namespace agl
{
	CShaderUID::CShaderUID()
		: uid_(Register())
	{
	}

	CShaderUID::CShaderUID(InvalidValue)
		: uid_(0u)
	{
	}

	CShaderUID::CShaderUID(CShaderUID &&other)
		: uid_(other.uid_)
	{
		other.uid_ = 0;
	}

	CShaderUID::CShaderUID(const CShaderUID &other)
		: uid_(other.uid_)
	{
		RegisteredIdentifiers()[uid_]++;
	}

	CShaderUID::CShaderUID(std::uint64_t uid)
		: uid_(uid)
	{
	}

	CShaderUID::~CShaderUID()
	{
		Unregister(*this);
	}

	CShaderUID& CShaderUID::operator=(CShaderUID &&other)
	{
		std::swap(other.uid_, uid_);

		return *this;
	}

	CShaderUID& CShaderUID::operator=(const CShaderUID &other)
	{
		uid_ = other.uid_;
		RegisteredIdentifiers()[uid_]++;

		return *this;
	}

	std::map<std::uint64_t, std::uint64_t>& CShaderUID::RegisteredIdentifiers()
	{
		static std::map<std::uint64_t, std::uint64_t> RegisteredIdentifiers_;
		return RegisteredIdentifiers_;
	}

	CShaderUID CShaderUID::Register()
	{
		std::uint64_t expected = 1u;

		for (const auto &m : RegisteredIdentifiers())
		{
			if (m.first != expected)
				break;

			expected++;
		}

		RegisteredIdentifiers().emplace(expected, 1u);
		return { expected };
	}

	void CShaderUID::Unregister(CShaderUID &uid)
	{
		if (uid == 0u)
			return;

		auto found = RegisteredIdentifiers().find(uid);

		if (found != RegisteredIdentifiers().end())
		{
			if (found->second > 1u)
				found->second--;
			else
				RegisteredIdentifiers().erase(found);
			uid.uid_ = 0u;
		}
	}

	CShaderUID::operator std::uint64_t() const
	{
		return uid_;
	}

}

*/
