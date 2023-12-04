#pragma once
#include <glm/glm.hpp>

#include "agl/graphics/ecs/component/transformable.hpp"
#include "agl/graphics/ecs/component/direction.hpp"

namespace agl
{
	/// <summary>
	/// A base class for the cameras.
	/// Virtual update_projection method will be called from get_projection method when the matrix will require update.
	/// </summary>
	class camera_base
	{
	public:
		static const direction s_world_direction;

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
		const glm::vec2& get_resolution() const;

		/// <summary>
		/// Set the dimension of the rendering screen.
		/// </summary>
		/// <param name="frame">The dimensions</returns>
		void set_resolution(const glm::vec2 &frame);

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
		/// Directs the camera forward direction towards given 'position'.
		/// </summary>
		/// <param name="position"></param>
		void look_at(const glm::vec3 &position);

		bool needs_update() const;

	protected:
		void update(transformable& transform, direction& dir);

	protected:
		transform m_projection;
		bool m_view_update;
		bool m_projection_update;

	private:
		friend class camera_system;

	private:
		glm::vec2 m_planes; // near / far
		glm::vec2 m_resolution;
		glm::vec3 m_look_at;

		bool m_look_at_update;
		transform m_view;
	};
}