template <class... Args>
CMesh<Args...>::CMesh()
	: myShader_(Shader::LIGHT_SHADER)
{
	uniformManager_.create("agl_model_transform", Shader::LIGHT_SHADER);
	uniformManager_.create("agl_model_inverse_transform", Shader::LIGHT_SHADER);
}

template <class... Args>
CUniformVector& CMesh<Args...>::getUniforms() const
{
	return uniforms_;
}

template <class... Args>
void CMesh<Args...>::addUniform(const IUniform &uniform)
{
	uniforms_.push_back(uniform.clone());
}

template <class... Args>
void CMesh<Args...>::setUniforms(const CUniformVector &shaderEntries)
{
	uniforms_ = shaderEntries;
}
template <class... Args>
const CUniformManager& CMesh<Args...>::getUniformManager() const
{
	return uniformManager_;
}

template <class... Args>
void CMesh<Args...>::redirectUniform(const std::string &name, const CShaderUID &shaderUID)
{
	uniformManager_.redirect(name, shaderUID);
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
	uniformManager_.pass("agl_model_transform", this->getTransform());
	uniformManager_.pass("agl_model_inverse_transform", this->getInverseTransform());

	uniforms_.passToShader();

	CShaderManager::GetShader(myShader_).setActive();
	this->CVertexObject::draw(renderer);
}