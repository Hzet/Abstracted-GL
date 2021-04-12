#pragma once

#include "mesh.hpp"

namespace agl
{
	/// <summary>
	/// Default model class for users that do not want or need to go into the details.
	/// Contains Vertices, Normals, Texture Coordinates.
	/// </summary>
	class CModel
		: public IDrawable,
		public CTransformable
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		CModel() = default;

		/// <summary>
		/// Move constructor.
		/// Update the meshes' parents.
		/// </summary>
		/// <param name="other">The other object</param>
		CModel(CModel &&other);

		/// <summary>
		/// Copy constructor.
		/// Update the meshes' parents.
		/// </summary>
		/// <param name="other">The other object</param>
		CModel(const CModel &other);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CModel() = default;

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		CModel& operator=(CModel &&other) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		CModel& operator=(const CModel &other) = default;

		/// <summary>
		/// Adds a 'mesh' object.
		/// </summary>
		/// <param name="mesh">The mesh</param>
		void addMesh(const CMesh &mesh);

		/// <summary>
		/// Sets the 'meshes'.
		/// </summary>
		/// <param name="meshes">The meshes</param>
		void setMeshes(const std::vector<CMesh> &meshes);

		/// <summary>
		/// Returns the meshes.
		/// </summary>
		/// <returns>The meshes</returns>
		const std::vector<CMesh>& getMeshes() const;

		/// <summary>
		/// Overridden draw method.
		/// </summary>
		/// <param name="renderer">The renderer</param>
		virtual void draw(const CRenderer &renderer) const override;

	private:
		std::vector<CMesh> meshes_;
	};
}