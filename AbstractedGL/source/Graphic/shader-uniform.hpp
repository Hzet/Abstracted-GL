#pragma once
#include <memory>

#include "shader-uid.hpp"

namespace agl
{
	class IUniform
	{
	public:
		const std::string& getName() const;
		virtual void setName(const std::string &name);
	
		virtual void passToShader() const = 0;

		virtual std::unique_ptr<IUniform> clone() const = 0;

	private:
		std::string name_;
	};
}