#include "shader-uniform.hpp"

namespace agl
{
	const std::string& IUniform::getName() const
	{
		return name_;
	}

	void IUniform::setName(const std::string &name)
	{
		name_ = name;
	}
}