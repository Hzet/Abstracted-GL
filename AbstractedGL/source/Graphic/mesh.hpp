#pragma once

#include "mesh-template.hpp"

namespace agl
{
	/// <summary>
	/// Default mesh class for users that do not want or need to go into the details.
	/// Contains Vertices, Normals, Texture Coordinates
	/// </summary>
	class CMesh
		: public TMesh<glm::vec3, glm::vec3, glm::vec2>
	{
	public:
		/// <summary>
		/// Returns the vertices.
		/// </summary>
		/// <returns>The vertices</returns>
		const std::vector<glm::vec3>& getVertices() const;

		/// <summary>
		/// Sets the vertices.
		/// </summary>
		/// <param name="vertices">The vertices</param>
		void setVertices(const std::vector<glm::vec3> &vertices);

		/// <summary>
		/// Returns the normals.
		/// </summary>
		/// <returns>The normals</returns>
		const std::vector<glm::vec3>& getNormals() const;

		/// <summary>
		/// Sets the normals.
		/// </summary>
		/// <param name="normals">The normals</param>
		void setNormals(const std::vector<glm::vec3> &normals);

		/// <summary>
		/// Returns the texture coordinates.
		/// </summary>
		/// <returns>The texture coordinates</returns>
		const std::vector<glm::vec2>& getTexCoords() const;

		/// <summary>
		/// Sets the texture coordinates.
		/// </summary>
		/// <param name="coords">The texture coordinates</param>
		void setTexCoords(const std::vector<glm::vec2> &coords);
	};
}