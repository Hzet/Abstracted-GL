#pragma once
#include "transform.hpp"

namespace agl
{
	/// <summary>
	/// A base class for objects that requires geometrical awareness in three dimensional space.
	/// </summary>
	class transformable
	{
	public:
		/// <summary>
		/// Set the scale, origin, position and rotation to be neutral (1, 0, 0, 0)
		/// and 'm_require_update' to false.
		/// </summary>
		transformable();

		/// <summary>
		/// Move constructor.
		/// Sets the parent transformation to nullptr.
		/// </summary>
		/// <param name=""></param>
		transformable(transformable &&other);

		/// <summary>
		/// Copy constructor.
		/// Sets the parent transformation to nullptr.
		/// </summary>
		/// <param name=""></param>
		transformable(const transformable &other);

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		transformable& operator=(transformable&&) = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		transformable& operator=(const transformable&) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~transformable() = default;

		/// <summary>
		/// Get the scale.
		/// </summary>
		/// <returns>
		/// The scale
		/// </returns>
		const glm::vec3& get_scale() const;

		/// <summary>
		/// Set the scale.
		/// </summary>
		/// <param name="scale">The new scale</param>
		void set_scale(const glm::vec3 &scale);

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
		void set_origin(const glm::vec3 &origin);

		/// <summary>
		/// Get the position.
		/// </summary>
		/// <returns>
		/// The position
		/// </returns>
		const glm::vec3& get_position() const;

		/// <summary>
		/// Set the position
		/// </summary>
		/// <param name="position">The new position</param>
		void set_position(const glm::vec3 &position);

		/// <summary>
		/// Get the rotation.
		/// </summary>
		/// <returns>
		/// The rotation
		/// </returns>
		const glm::vec3& get_rotation() const;

		/// <summary>
		/// Set the rotation.
		/// </summary>
		/// <param name="rotation">The rotation</param>
		void set_rotation(const glm::vec3 &rotation);

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
		void set_transform(const transform &transform);

		/// <summary>
		/// Get the transform matrix.
		/// </summary>
		/// <returns>
		/// The transform
		/// </returns>
		const transform& get_transform() const;

		/// <summary>
		/// Get the inverse transform matrix.
		/// </summary>
		/// <returns>
		/// The inverse transform
		/// </returns>
		const transform& get_inverse_transform() const;

		bool needs_update() const;

	private:
		/// <summary>
		/// Update matrices.
		/// </summary>
		void update() const;

		glm::vec3 m_scale;
		glm::vec3 m_origin;
		glm::vec3 m_position;
		glm::vec3 m_rotation;

		mutable bool m_require_update;
		mutable transform m_transform;
		mutable transform m_inverse_transform;
	};
}