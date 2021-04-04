#pragma once

#include "shader-uniform.hpp"

namespace agl
{
	/// <summary>
	/// An interface for uniforms that aggregate other uniforms.
	/// This interface keeps track of the aggregated elements and thus it automatically passes all uniforms added to it's shaders.
	/// So the uniform be able to keep track of contained uniforms one must 'addUniform' to the pack.
	/// When copying the pack one must re-add the uniforms to the pack and copy it's values by himself.
	/// </summary>
	class IUniformPack
		: public IUniform
	{
	public:
		using IUniform::IUniform;

		/// <summary>
		/// Move constructor.
		/// Does not move it's member uniforms.
		/// </summary>
		/// <param name="other">The other object</param>
		IUniformPack(IUniformPack &&other);

		/// <summary>
		/// Copy constructor.
		/// Does not copy it's member uniforms.
		/// </summary>
		/// <param name="other">The other object</param>
		IUniformPack(const IUniformPack &other);

		/// <summary>
		/// Move assignment operator.
		/// Does not move it's member uniforms.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>A reference to this</returns>
		IUniformPack& operator=(IUniformPack &&other);

		/// <summary>
		/// Copy assignment operator.
		/// Does not copy it's member uniforms.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>A reference to this</returns>
		IUniformPack& operator=(const IUniformPack &other);

		/// <summary>
		/// Default virtual destructor.
		/// </summary>
		virtual ~IUniformPack() = default;

		/// <summary>
		/// Adds the 'uniform' to tracked elements. 
		/// </summary>
		/// <param name="uniform">A reference to the uniform, must not be a temporary.</param>
		void addUniform(IUniform &uniform);

		/// <summary>
		/// Passes tracked uniforms to it's shaders.
		/// </summary>
		virtual void passUniform() const override;

		/// <summary>
		/// Sets the index of this array instance and updates the scopes of tracked uniforms.
		/// </summary>
		/// <param name="index">The index</param>
		virtual void setIndex(std::uint64_t index) override;

		/// <summary>
		/// Set all uniforms to be send to the shader assigned to 'shaderUID'.
		/// </summary>
		/// <param name="shaderUID"></param>
		virtual void setShader(const CShaderUID &shaderUID) override;

	private:
		/// <summary>
		/// Set all uniforms to be send to the shader assigned to 'shaderUID'.
		/// </summary>
		/// <param name="name">new namespace</param>
		virtual void updateNamespace(const std::string &name) override;

		std::vector<IUniform*> uniforms_;
	};
}