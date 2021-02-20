template <class... Args>
const CVertexLayout CMesh<Args...>::Layout_ = CMesh<Args...>::GetLayout();

template <class... Args>
CMesh<Args...>::CMesh()
	: myShader_(Shader::LIGHT_SHADER)
{
	uniformManager_.create("agl_model_transform", Shader::LIGHT_SHADER);
	uniformManager_.create("agl_model_inverse_transform", Shader::LIGHT_SHADER);
}

template <class... Args>
void CMesh<Args...>::addVertex(Args&&... args)
{
	vbUpdate_ = true;

	vertices_.push_back(std::forward<Args>(args)...);
}

template <class... Args>
template <std::uint64_t I> 
auto& CMesh<Args...>::getVertexAttribute(const std::uint64_t index)
{
	vbUpdate_ = true;

	return vertices_.get<I>(index);
}

template <class... Args>
template <std::uint64_t I> 
const auto& CMesh<Args...>::getVertexAttribute(const std::uint64_t index) const
{
	return vertices_.get<I>(index);
}

template <class... Args>
void CMesh<Args...>::setVertices(const CTupleBuffer<Args...> &vertices)
{
	vbUpdate_ = true;
	vertices_ = vertices;
}

template <class... Args>
template <std::size_t I, class T>
void CMesh<Args...>::setVertices(const std::vector<T> &vertices)
{
	setVertices<I>(vertices.data(), vertices.size());
}

template <class... Args>
template <std::size_t I, class T>
void CMesh<Args...>::setVertices(T const * const vertices, const std::uint64_t count)
{
	vbUpdate_ = true;

	if (count != vertices_.getCount())
		vertices_.resize(count);

	for (std::uint64_t i = 0u; i < count; i++)
		vertices_.get<I>(i) = *(vertices + i);
}

template <class... Args>
void CMesh<Args...>::setIndices(const std::vector<std::uint32_t> &indices)
{
	ibUpdate_ = true;
	indices_ = indices;
}

template <class... Args>
void CMesh<Args...>::setIndices(std::uint32_t const * const indices, const std::uint64_t count)
{
	ibUpdate_ = true;
	
	indices_.resize(count);

	for (std::uint64_t i = 0u; i < count; i++)
		indices_[i] = *(indices + i);
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
std::uint64_t CMesh<Args...>::getDrawType() const
{
	return drawType_;
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
void CMesh<Args...>::setDrawType(const std::uint64_t drawType)
{
	drawType_ = drawType;
}

template <class... Args>
CVertexLayout CMesh<Args...>::GetLayout()
{
	CVertexLayout result;
	GetLayout_impl(result);

	return result;
}

template <class... Args>
template <std::size_t I>
void CMesh<Args...>::GetLayout_impl(CVertexLayout &result)
{
	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	result.addElement<type>();

	if constexpr (I + 1u < sizeof...(Args))
		GetLayout_impl<I + 1u>(result);
}

template <class... Args>
void CMesh<Args...>::draw(const CRenderer &renderer) const
{
	if (vbUpdate_)
		updateVBuffer();

	if (ibUpdate_)
		updateIBuffer();

	if (ibUpdate_ || vbUpdate_)
		updateVArray();

	uniformManager_.pass("agl_model_transform", getTransform());
	uniformManager_.pass("agl_model_inverse_transform", getInverseTransform());

	uniforms_.passToShader();

	CShaderManager::GetShader(myShader_).setActive();
	renderer.draw(vArray_, drawType_);
}

template <class... Args>
void CMesh<Args...>::updateIBuffer() const
{
	if(!indices_.empty())
		iBuffer_.allocate(indices_.data(), indices_.size());
}

template <class... Args>
void CMesh<Args...>::updateVBuffer() const
{
	vBuffer_.allocate(vertices_.getData(), vertices_.getSize(), vertices_.getCount());
}

template <class... Args>
void CMesh<Args...>::updateVArray() const
{
	vArray_.setBuffer(vBuffer_, Layout_, iBuffer_);

	vbUpdate_ = false;
	ibUpdate_ = false;
}