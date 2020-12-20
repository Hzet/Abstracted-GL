#pragma once

#include <glm/glm.hpp>

namespace agl
{
	class CTransform
	{
	public:
		CTransform();
		CTransform(const glm::mat4 &matrix);
		CTransform(CTransform&&) = default;
		CTransform(const CTransform&) = default;
		virtual ~CTransform() = default;

		CTransform& operator=(CTransform&&) = default;
		CTransform& operator=(const CTransform&) = default;

		void scale(const glm::vec3 &scale);
		void rotate(const glm::vec3 &angle);
		void translate(const glm::vec3 &offset);

		CTransform getInverse() const;

		operator const glm::mat4&() const;
		CTransform& operator*=(const CTransform &other);
		CTransform operator*(const CTransform &other) const;

	private:
		glm::mat4 matrix_;
	};
}