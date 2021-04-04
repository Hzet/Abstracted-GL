#pragma once

#include "transform.hpp"

namespace agl
{
	/// <summary>
	/// A base class for objects that requires geometrical awareness in three dimensional space.
	/// </summary>
	class CTransformable
	{
	public:
		/// <summary>
		/// Set the scale, origin, position and rotation to be neutral (1, 0, 0, 0)
		/// and 'requireUpdate_' to false.
		/// </summary>
		CTransformable();

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name=""></param>
		CTransformable(CTransformable&&) = default;

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name=""></param>
		CTransformable(const CTransformable&) = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CTransformable& operator=(CTransformable&&) = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		CTransformable& operator=(const CTransformable&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CTransformable() = default;

		/// <summary>
		/// Get the scale.
		/// </summary>
		/// <returns>
		/// The scale
		/// </returns>
		const glm::vec3& getScale() const;

		/// <summary>
		/// Set the scale.
		/// </summary>
		/// <param name="scale">The new scale</param>
		void setScale(const glm::vec3 &scale);

		/// <summary>
		/// Get the origin.
		/// </summary>
		/// <returns>
		/// The origin
		/// </returns>
		const glm::vec3& getOrigin() const;

		/// <summary>
		/// Set the origin.
		/// </summary>
		/// <param name="origin">The origin</param>
		void setOrigin(const glm::vec3 &origin);

		/// <summary>
		/// Get the position.
		/// </summary>
		/// <returns>
		/// The position
		/// </returns>
		const glm::vec3& getPosition() const;

		/// <summary>
		/// Set the position
		/// </summary>
		/// <param name="position">The new position</param>
		void setPosition(const glm::vec3 &position);

		/// <summary>
		/// Get the rotation.
		/// </summary>
		/// <returns>
		/// The rotation
		/// </returns>
		const glm::vec3& getRotation() const;

		/// <summary>
		/// Set the rotation.
		/// </summary>
		/// <param name="rotation">The rotation</param>
		void setRotation(const glm::vec3 &rotation);

		/// <summary>
		/// Move by an 'offset'.
		/// </summary>
		/// <param name="offset">The offset</param>
		void move(const glm::vec3 &offset);

		/// <summary>
		/// Scale by a 'scale'
		/// </summary>
		/// <param name="ratio">The ratio</param>
		void scale(const glm::vec3 &ratio);

		/// <summary>
		/// Rotate by an 'angle'
		/// </summary>
		/// <param name="angle">The angle</param>
		void rotate(const glm::vec3 &angle);

		/// <summary>
		/// Sets the transformation matrix.
		/// </summary>
		/// <param name="transform">The matrix</param>
		void setTransform(const CTransform &transform);

		/// <summary>
		/// Get the transform matrix.
		/// </summary>
		/// <returns>
		/// The transform
		/// </returns>
		const CTransform& getTransform() const;

		/// <summary>
		/// Get the inverse transform matrix.
		/// </summary>
		/// <returns>
		/// The inverse transform
		/// </returns>
		const CTransform& getInverseTransform() const;

	private:
		/// <summary>
		/// Update matrices.
		/// </summary>
		void update() const;

		glm::vec3 scale_;
		glm::vec3 origin_;
		glm::vec3 position_;
		glm::vec3 rotation_;

		mutable bool requireUpdate_;
		mutable CTransform transform_;
		mutable CTransform inverseTransform_;
	};
}