template <class... Args>
CMesh<Args...>::CMesh()
	: myShader_(Shader::LIGHT_SHADER),
	transform("agl_model_transform", { *this }, { &CTransformable::getTransform }, nullptr, Shader::LIGHT_SHADER),
	inverseTransform("agl_model_inverse_transform", { *this }, { &CTransformable::getInverseTransform }, nullptr, Shader::LIGHT_SHADER)
{
}

template <class... Args>
CMesh<Args...>::CMesh(CMesh &&other)
	: graphics::CVertexObject<Args...>(std::move(other)),
	transform(std::move(other.transform)),
	inverseTransform(std::move(other.inverseTransform))
{
}

template <class... Args>
CMesh<Args...>::CMesh(const CMesh &other)
	: graphics::CVertexObject<Args...>(other),
	transform(other.transform, { *this }),
	inverseTransform(other.inverseTransform, { *this })
{
}

template <class... Args>
void CMesh<Args...>::addUniform(const IUniform &uniform)
{
	uniforms_.push_back(uniform);
}

template <class... Args>
template <typename ForwardIterator>
void CMesh<Args...>::setUniforms(ForwardIterator first, ForwardIterator last)
{
	uniforms_.assign(first, last);
}

template <class... Args>
void CMesh<Args...>::setShader(const CShaderUID &uid)
{
	myShader_ = uid;
}

template <class... Args>
const CShaderUID& CMesh<Args...>::getShader() const
{
	return myShader_;
}

template <class... Args>
void CMesh<Args...>::draw(const CRenderer &renderer) const
{
	transform.passUniform();
	inverseTransform.passUniform();

	for (const auto &v : uniforms_)
		v->passUniform();

	CShaderManager::GetShader(myShader_).setActive();
	this->CVertexObject::draw(renderer);
}