#pragma once
#include <glm/glm.hpp>

#include "graphics/ecs/component/transform.hpp"

namespace agl
{
	/// <summary>
	/// Aggregation struct to store direction vectors.
	/// </summary>
	struct direction_matrix
	{
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	/// <summary>
	/// A base class for the cameras.
	/// Virtual update_projection method will be called from get_projection method when the matrix will require update.
	/// </summary>
	class camera_base
	{
	public:
		static const direction_matrix s_world_direction;

		/// <summary>
		/// Set transform properties to 0 or 1 for scale and planes to {0, 100}.
		/// </summary>
		camera_base();
		virtual ~camera_base() = default;

		/// <summary>
		/// Get the dimension of the rendering screen.
		/// </summary>
		/// <returns>
		/// The dimensions
		/// </returns>
		const glm::uvec2& get_frame_dimensions() const;

		/// <summary>
		/// Set the dimension of the rendering screen.
		/// </summary>
		/// <param name="frame">The dimensions</returns>
		void set_frame_dimensions(const glm::uvec2 &frame);

		/// <summary>
		/// Get the camera's near and far 'planes'.
		/// </summary>
		/// <returns>
		/// The planes 
		/// </returns>
		const glm::vec2& get_planes() const;

		/// <summary>
		/// Set the camera's near and far 'planes'.
		/// </summary>
		/// <param name="planes">The planes</param>
		void set_planes(const glm::vec2 &planes);

		/// <summary>
		/// Get the view's 'scale'.
		/// </summary>
		/// <returns>
		/// The scale
		/// </returns>
		const glm::vec3& get_scale() const;

		/// <summary>
		/// Set the view's 'scale'.
		/// </summary>
		/// <param name="scale">The scale</param>
		void set_scale(const glm::vec3 &scale);

		/// <summary>
		/// Get the 'position' of the camera.
		/// </summary>
		/// <returns>
		/// The position
		/// </returns>
		const glm::vec3& get_position() const;

		/// <summary>
		/// Set the position of the camera.
		/// </summary>
		/// <param name="position">The position</param>
		void set_position(const glm::vec3 &position);

		/// <summary>
		/// Get the 'rotation' of the camera.
		/// </summary>
		/// <returns>
		/// The roatation
		/// </returns>
		const glm::vec3& get_rotation() const;

		/// <summary>
		/// Set the 'rotation' of the camera.
		/// </summary>
		/// <param name="rotation">The rotation</param>
		void set_rotation(const glm::vec3 &rotation);

		/// <summary>
		/// Scale the object by a 'scale'.
		/// </summary>
		/// <param name="scale"></param>
		void scale(const glm::vec3 &scale);

		/// <summary>
		/// Move the camera by an 'offset'.
		/// </summary>
		/// <param name="offset">The offset</param>
		void move(const glm::vec3 &offset);

		/// <summary>
		/// Rotate the camera by an 'angle'.
		/// </summary>
		/// <param name="angle">The angle</param>
		void rotate(const glm::vec3 &angle);

		/// <summary>
		/// Get the 'm_view' matrix.
		/// </summary>
		/// <returns>
		/// The view matrix
		/// </returns>
		const transform& get_view() const;

		/// <summary>
		/// Get the 'm_projection' matrix.
		/// </summary>
		/// <returns>
		/// The projection matrix
		/// </returns>
		const transform& get_projection() const;

		/// <summary>
		/// Get the directions of the camera.
		/// </summary>
		/// <returns>
		/// The direction
		/// </returns>
		const direction_matrix& get_direction() const;

		/// <summary>
		/// Directs the camera forward direction towards given 'position'.
		/// </summary>
		/// <param name="position"></param>
		void look_at(const glm::vec3 &position);

	protected:
		/// <summary>
		/// Recalculate the 'm_view' matrix.
		/// </summary>
		void update_view() const;

		/// <summary>
		/// Recalculate the 'm_projection' matrix.
		/// </summary>
		virtual void update_projection() const = 0;

		mutable transform m_projection;
		mutable bool m_view_update;
		mutable bool m_proj_update;

	private:
		glm::vec2 m_planes; // near / far
		glm::uvec2 m_frame_dimensions;
		glm::vec3 m_scale;
		glm::vec3 m_position;
		glm::vec3 m_rotation; // yaw, pitch, roll

		mutable transform m_view;
		mutable direction_matrix m_direction;
	};
}