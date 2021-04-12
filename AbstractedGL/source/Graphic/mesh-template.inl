template <class... Args>
TMesh<Args...>::TMesh()
	: myShader_(Shader::LIGHT_SHADER),
	transform("agl_model_transform", { *this }, { &CTransformable::getTransform }, nullptr, Shader::LIGHT_SHADER),
	inverseTransform("agl_model_inverse_transform", { *this }, { &CTransformable::getInverseTransform }, nullptr, Shader::LIGHT_SHADER)
{
}

template <class... Args>
TMesh<Args...>::TMesh(TMesh &&other)
	: graphics::TVertexObject<Args...>(std::move(other)),
	transform(std::move(other.transform), { *this }),
	inverseTransform(std::move(other.inverseTransform), { *this }),
	uniforms_(std::move(other.uniforms_)),
	myShader_(std::move(other.myShader_))
{
}

template <class... Args>
TMesh<Args...>::TMesh(const TMesh &other)
	: graphics::TVertexObject<Args...>(other),
	transform(other.transform, { *this }),
	inverseTransform(other.inverseTransform, { *this }),
	myShader_(other.myShader_)
{
	uniforms_.resize(other.uniforms_.size());
	for (std::uint64_t i = 0u; i < uniforms_.size(); i++)
		uniforms_[i] = other.uniforms_[i]->clone();
}

template <class... Args>
TMesh<Args...>& TMesh<Args...>::operator=(TMesh<Args...> &&other)
{
	graphics::TVertexObject<Args...>::operator=(std::forward<graphics::TVertexObject<Args...>>(other));

	transform = std::move(TUniform<const CTransform&, const CTransformable&>(other.transform, { *this }));
	inverseTransform = std::move(TUniform<const CTransform&, const CTransformable&>(other.inverseTransform, { *this }));
	uniforms_ = std::move(other.uniforms_);

	return *this;
}

template <class... Args>
TMesh<Args...>& agl::TMesh<Args...>::operator=(const TMesh<Args...> &other)
{
	graphics::TVertexObject<Args...>::operator=(other);

	transform = { other.transform, { *this } };
	inverseTransform = { other.inverseTransform, { *this } };

	uniforms_.resize(other.uniforms_.size());
	for (std::uint64_t i = 0u; i < uniforms_.size(); i++)
		uniforms_[i] = other.uniforms_[i]->clone();

	return *this;
}


template <class... Args>
void TMesh<Args...>::addUniform(const IUniform &uniform)
{
	uniforms_.push_back(uniform.clone());
}

template <class... Args>
void TMesh<Args...>::setShader(const CShaderUID &uid)
{
	myShader_ = uid;
}

template <class... Args>
const CShaderUID& TMesh<Args...>::getShader() const
{
	return myShader_;
}

template <class... Args>
void TMesh<Args...>::draw(const CRenderer &renderer) const
{
	transform.passUniform();
	inverseTransform.passUniform();

	for (const auto &v : uniforms_)
		v->passUniform();

	CShaderManager::GetShader(myShader_).setActive();
	this->TVertexObject::draw(renderer);
}