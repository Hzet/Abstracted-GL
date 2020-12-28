template <class... Args>
const CVertexLayout CShape<Args...>::Layout_ = CShape<Args...>::GetLayout();

template <class... Args>
void CShape<Args...>::addPoint(Args&&... args)
{
	vbUpdate_ = true;

	vertices_.push_back(std::forward<Args>(args)...);
}

template <class... Args>
template <std::uint64_t I> 
auto& CShape<Args...>::get(const std::uint64_t index)
{
	vbUpdate_ = true;

	return vertices_.get<I>(index);
}

template <class... Args>
template <std::uint64_t I> 
const auto& CShape<Args...>::get(const std::uint64_t index) const
{
	return vertices_.get<I>(index);
}


template <class... Args>
void CShape<Args...>::setVertices(const CTupleBuffer<Args...> &vertices)
{
	vbUpdate_ = true;
	vertices_ = vertices;
}

template <class... Args>
template <std::size_t I, class T>
void CShape<Args...>::setVertices(const std::vector<T> &vertices)
{
	setVertices<I>(vertices.data(), vertices.size());
}

template <class... Args>
template <std::size_t I, class T>
void CShape<Args...>::setVertices(T const * const vertices, const std::uint64_t count)
{
	vbUpdate_ = true;

	if (count != vertices_.getCount())
		vertices_.resize(count);

	for (std::uint64_t i = 0u; i < count; i++)
		vertices_.get<I>(i) = *(vertices + i);

}

template <class... Args>
void CShape<Args...>::setIndices(const std::vector<std::uint32_t> &indices)
{
	ibUpdate_ = true;
	indices_ = indices;
}

template <class... Args>
void CShape<Args...>::setIndices(std::uint32_t const * const indices, const std::uint64_t count)
{
	ibUpdate_ = true;
	
	indices_.resize(count);

	for (std::uint64_t i = 0u; i < count; i++)
		indices_[i] = *(indices + i);
}

template <class... Args>
const IShaderData& CShape<Args...>::getShaderData() const
{
	return *shaderData_;
}

template <class... Args>
void CShape<Args...>::setShaderData(const IShaderData &data)
{
	shaderData_ = data.clone();
}

template <class... Args>
std::uint64_t CShape<Args...>::getDrawType() const
{
	return drawType_;
}

template <class... Args>
void CShape<Args...>::setDrawType(const std::uint64_t drawType)
{
	drawType_ = drawType;
}

template <class... Args>
CVertexLayout CShape<Args...>::GetLayout()
{
	CVertexLayout result;
	GetLayout_impl(result);

	return result;
}

template <class... Args>
template <std::size_t I>
void CShape<Args...>::GetLayout_impl(CVertexLayout &result)
{
	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	result.addElement<type>();

	if constexpr (I + 1u < sizeof...(Args))
		GetLayout_impl<I + 1u>(result);
}

template <class... Args>
void CShape<Args...>::draw(const CRenderer &renderer) const
{
	if (vbUpdate_)
		updateVBuffer();

	if (ibUpdate_)
		updateIBuffer();

	if (ibUpdate_ || vbUpdate_)
		updateVArray();

	renderer.getActiveShader().setMat4("model_transform", getTransform());

	renderer.draw(vArray_, drawType_);
}

template <class... Args>
void CShape<Args...>::updateIBuffer() const
{
	if(!indices_.empty())
		iBuffer_.allocate(indices_.data(), indices_.size());
}

template <class... Args>
void CShape<Args...>::updateVBuffer() const
{
	vBuffer_.allocate(vertices_.getData(), vertices_.getSize(), vertices_.getCount());
}

template <class... Args>
void CShape<Args...>::updateVArray() const
{
	vArray_.setBuffer(vBuffer_, Layout_, iBuffer_);

	vbUpdate_ = false;
	ibUpdate_ = false;
}