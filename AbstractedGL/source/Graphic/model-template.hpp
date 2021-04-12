#pragma once

#include "mesh-template.hpp"

namespace agl
{
	template <class... Args>
	class TModel
		: public IDrawable,
		public CTransformable
	{
	public:
		/// <summary>
		/// Default construct.
		/// </summary>
		TModel() = default;

		/// <summary>
		/// Move constructor.
		/// Update the meshes' parents.
		/// </summary>
		/// <param name="other">The other object</param>
		TModel(TModel &&other);

		/// <summary>
		/// Copy constructor.
		/// Update the meshes' parents.
		/// </summary>
		/// <param name="other">The other object</param>
		TModel(const TModel &other);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~TModel() = default;

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		TModel& operator=(TModel &&other) = default;

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		TModel& operator=(const TModel &other) = default;

		/// <summary>
		/// Adds a 'mesh' object.
		/// </summary>
		/// <param name="mesh">The mesh</param>
		void addMesh(const TMesh<Args...> &mesh);

		/// <summary>
		/// Sets the 'meshes'.
		/// </summary>
		/// <param name="meshes">The meshes</param>
		void setMeshes(const std::vector<TMesh<Args...>> &meshes);

		/// <summary>
		/// Returns the meshes.
		/// </summary>
		/// <returns>The meshes</returns>
		const std::vector<TMesh<Args...>>& getMeshes() const;

		/// <summary>
		/// Overridden draw method.
		/// </summary>
		/// <param name="renderer">The renderer</param>
		virtual void draw(const CRenderer &renderer) const override;

	private:
		std::vector<TMesh<Args...>> meshes_;
	};

#include "model-template.inl"
}