template <class... Args>
TModel<Args...>::TModel(TModel &&other)
	: CTransformable(std::move(other))
{
	meshes_.resize(other.meshes_.size());
	for (std::uint64_t i = 0u; i < meshes_.size(); i++)
	{
		meshes_[i] = std::move(other.meshes_[i]);
		meshes_[i].setParent(*this);
	}
}

template <class... Args>
TModel<Args...>::TModel(const TModel &other)
	: CTransformable(other)
{
	meshes_.resize(other.meshes_.size());
	for (std::uint64_t i = 0u; i < meshes_.size(); i++)
	{
		meshes_[i] = other.meshes_[i];
		meshes_[i].setParent(*this);
	}
}

template <class... Args>
void TModel<Args...>::addMesh(const TMesh<Args...> &mesh)
{
	meshes_.push_back(mesh);
	meshes_.back().setParent(*this);
}

template <class... Args>
void TModel<Args...>::setMeshes(const std::vector<TMesh<Args...>> &meshes)
{
	meshes_ = meshes;

	for (auto &v : meshes_)
		v.setParent(*this);
}

template <class... Args>
const std::vector<TMesh<Args...>>& TModel<Args...>::getMeshes() const
{
	return meshes_;
}

template <class... Args>
void TModel<Args...>::draw(const CRenderer &renderer) const
{
	for (const auto &v : meshes_)
		v.draw(renderer);
}