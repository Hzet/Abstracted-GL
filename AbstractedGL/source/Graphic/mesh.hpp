#pragma once

#include "vertex-object.hpp"
#include "shader-manager.hpp"
#include "shader-uniform-variable.hpp"

namespace agl
{
	/// <summary>
	/// Represents the mesh, to which is possible to add different non-owning uniforms.
	/// </summary>
	template <class... Args>
	class CMesh
		: public graphics::CVertexObject<Args...>
	{
	public:
		/// <summary>
		/// Constructor. 
		/// Sets the 'transform' and 'inverseTransform' destinations to LIGHT_SHADER.
		/// </summary>
		CMesh();

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CMesh(CMesh &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		CMesh(const CMesh &other);

		/// <summary>
		/// Default move assignment operator.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		CMesh& operator=(CMesh &&other) = default;

		/// <summary>
		/// Default copy assignment operator.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		CMesh& operator=(const CMesh &other) = default;

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~CMesh() = default;
		
		/// <summary>
		/// Returns assigned destination shader.
		/// </summary>
		/// <returns>The shader's unique identifier</returns>
		const CShaderUID& getShader() const;

		/// <summary>
		/// Sets the destination shader.
		/// </summary>
		/// <param name="uid">The shader's unique identifier</param>
		void setShader(const CShaderUID &uid);

		/// <summary>
		/// Adds a uniform to be send on every 'draw' call.
		/// </summary>
		/// <param name="uniform">The uniform</param>
		void addUniform(const IUniform &uniform);

		/// <summary>
		/// Draw the vertices and pass all uniforms to the shaders.
		/// </summary>
		/// <param name="renderer">The renderer</param>
		virtual void draw(const CRenderer &renderer) const override;
	
		CUniform<const CTransform&, const CTransformable&> transform;
		CUniform<const CTransform&, const CTransformable&> inverseTransform;
	private:
		CShaderUID myShader_;
		std::vector<std::unique_ptr<IUniform>> uniforms_;
	};

#include "mesh.inl"
}