#include "model.hpp"

namespace agl
{
	CModel::CModel(CModel &&other)
		: CTransformable(std::move(other))
	{
		meshes_.resize(other.meshes_.size());
		for (std::uint64_t i = 0u; i < meshes_.size(); i++)
		{
			meshes_[i] = std::move(other.meshes_[i]);
			meshes_[i].setParent(*this);
		}
	}

	CModel::CModel(const CModel &other)
		: CTransformable(other)
	{
		meshes_.resize(other.meshes_.size());
		for (std::uint64_t i = 0u; i < meshes_.size(); i++)
		{
			meshes_[i] = other.meshes_[i];
			meshes_[i].setParent(*this);
		}
	}

	void CModel::addMesh(const CMesh &mesh)
	{
		meshes_.push_back(mesh);
		meshes_.back().setParent(*this);
	}

	void CModel::setMeshes(const std::vector<CMesh> &meshes)
	{
		meshes_ = meshes;
		meshes_.back().setParent(*this);
	}

	const std::vector<agl::CMesh>& CModel::getMeshes() const
	{
		return meshes_;
	}

	void CModel::draw(const CRenderer &renderer) const
	{
		for (auto &v : meshes_)
			v.draw(renderer);
	}

}