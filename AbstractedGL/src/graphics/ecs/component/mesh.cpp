#include "graphics/object/mesh.hpp"

namespace agl
{

	const std::vector<glm::vec3>& CMesh::getVertices() const
	{
		return TMesh::getVertices<0u>();
	}

	void CMesh::setVertices(const std::vector<glm::vec3> &vertices)
	{
		TMesh::setVertices<0u>(vertices);
	}

	const std::vector<glm::vec3>& CMesh::getNormals() const
	{
		return TMesh::getVertices<1u>();
	}

	void CMesh::setNormals(const std::vector<glm::vec3> &normals)
	{
		TMesh::setVertices<1u>(normals);
	}

	const std::vector<glm::vec2>& CMesh::getTexCoords() const
	{
		return TMesh::getVertices<2u>();
	}

	void CMesh::setTexCoords(const std::vector<glm::vec2> &coords)
	{
		TMesh::setVertices<2u>(coords);
	}

}

