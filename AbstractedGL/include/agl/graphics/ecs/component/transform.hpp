#pragma once
#include <glm/glm.hpp>

namespace agl
{
	/// <summary>
	/// A 4x4 matrix wrapper providing basic geometric operations.
	/// </summary>
	class transform
	{
	public:
		/// <summary>
		/// create an identity transform.
		/// </summary>
		transform();

		/// <summary>
		/// create the transform from a matrix.
		/// </summary>
		/// <param name="matrix">The matrix</param>
		transform(const glm::mat4 &matrix);

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		transform(transform&&) = default;

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		transform(const transform&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~transform() = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		transform& operator=(transform&&) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		transform& operator=(const transform&) = default;

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
		transform& operator*=(const transform &other);

		/// <summary>
		/// Get the combination transform of this transform with the 'other'.
		/// </summary>
		/// <param name="other">The transform</param>
		/// <returns>
		/// Newly created transform
		/// </returns>
		transform operator*(const transform &other) const;

	private:
		glm::mat4 m_matrix;
	};
}