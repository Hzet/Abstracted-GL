#pragma once

#include <glm/glm.hpp>

namespace agl
{
	/// <summary>
	/// A 4x4 matrix wrapper providing basic geometric operations.
	/// </summary>
	class CTransform
	{
	public:
		/// <summary>
		/// Create an identity transform.
		/// </summary>
		CTransform();

		/// <summary>
		/// Create the transform from a matrix.
		/// </summary>
		/// <param name="matrix">The matrix</param>
		CTransform(const glm::mat4 &matrix);

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CTransform(CTransform&&) = default;

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		CTransform(const CTransform&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CTransform() = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CTransform& operator=(CTransform&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CTransform& operator=(const CTransform&) = default;

		/// <summary>
		/// Scale the matrix by a 'scale'.
		/// </summary>
		/// <param name="scale">The scale</param>
		void scale(const glm::vec3 &scale);

		/// <summary>
		/// Rotate the matrix by an 'angle'.
		/// </summary>
		/// <param name="angle">The angle</param>
		void rotate(const glm::vec3 &angle);

		/// <summary>
		/// Translate the matrix by an 'offset'.
		/// </summary>
		/// <param name="offset">The offset</param>
		void translate(const glm::vec3 &offset);

		/// <summary>
		/// Cast the transform to a 4x4 matrix.
		/// </summary>
		/// <returns>
		/// The matrix
		/// </returns>
		operator const glm::mat4&() const;

		/// <summary>
		/// Combine the transform with the 'other'.
		/// </summary>
		/// <param name="other">The transform</param>
		/// <returns>
		/// Reference to this
		/// </returns>
		CTransform& operator*=(const CTransform &other);

		/// <summary>
		/// Get the combination transform of this transform with the 'other'.
		/// </summary>
		/// <param name="other">The transform</param>
		/// <returns>
		/// Newly created transform
		/// </returns>
		CTransform operator*(const CTransform &other) const;

	private:
		glm::mat4 matrix_;
	};
}