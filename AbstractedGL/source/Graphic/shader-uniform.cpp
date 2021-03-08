#include "shader-uniform.hpp"
#include "../System/assert.hpp"

#include <string>
#include <regex>

namespace agl
{
	static void SetIndex(std::string &str, std::uint64_t index)
	{
		static const std::regex Pattern("\\[[0-9]{1,}\\]$");

		std::smatch match;

		if (std::regex_search(str, match, Pattern))
			str.erase(str.cbegin() + match.position(0u), str.cbegin() + match.position(0u) + match[0u].length());

		str += "[" + std::to_string(index) + "]";
	}

	IUniform::IUniform(const std::string &name, IUniform const * const parent/* = nullptr*/)
		: name_(name),
		fullname_(name)
	{
		if (parent != nullptr)
			setFullName(parent->fullname_);
	}

	IUniform::IUniform(IUniform &&other)
		: name_(std::move(other.name_)),
		fullname_(std::move(other.fullname_))
	{
	}

	IUniform::IUniform(const IUniform &other)
		: name_(other.name_),
		fullname_(other.fullname_)
	{
	}


	IUniform::IUniform(const IUniform &other, IUniform const * const parent)
		: name_(other.name_),
		fullname_(name_)
	{
		if (parent != nullptr)
			setFullName(parent->fullname_);
	}

	void IUniform::setIndex(std::uint64_t index)
	{
		SetIndex(name_, index);
		SetIndex(fullname_, index);
	}

	const std::string& IUniform::getName() const
	{
		return name_;
	}

	const std::string& IUniform::getFullName() const
	{
		return fullname_;
	}

	void IUniform::updateNamespace(const std::string &name)
	{
		fullname_ = name + "." + name_;
	}

	void IUniform::setFullName(const std::string &fullname)
	{
		if (fullname.empty())
			fullname_ = name_;
		else
			fullname_ = fullname + "." + name_;
	}
}