#include "shader-uniform-vector.hpp"

namespace agl
{
	CUniformVector::CUniformVector(const CUniformVector &other)
	{
		resize(other.count());
		for (std::uint64_t i = 0u; i < count(); i++)
			(*this)[i] = other[i]->clone();
	}

	CUniformVector& CUniformVector::operator=(const CUniformVector &other)
	{
		resize(other.count());
		for (std::uint64_t i = 0u; i < count(); i++)
			(*this)[i] = other[i]->clone();

		return *this;
	}

	void CUniformVector::passToShader() const
	{
		for (auto it = cbegin(); it != cend(); ++it)
			(*it)->passToShader();
	}
}