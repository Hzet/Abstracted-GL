#pragma once
#include <glm/glm.hpp>

#include "graphics/ecs/component/transformable.hpp"

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

		bool needs_update() const;

	protected:
		void update(transformable& transform);

		/// <summary>
		/// Recalculate the 'm_projection' matrix.
		/// </summary>
		virtual void update_projection() = 0;

	protected:
		transform m_projection;
		bool m_needs_update;

	private:
		friend class camera_system;

	private:
		glm::vec2 m_planes; // near / far
		glm::uvec2 m_frame_dimensions;
		glm::vec3 m_look_at;

		bool m_look_at_update;
		transform m_view;
		direction_matrix m_direction;
	};
}