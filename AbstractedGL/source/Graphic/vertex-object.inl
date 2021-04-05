template <class... Args>
const CVertexLayout TVertexObject<Args...>::Layout_ = TVertexObject<Args...>::GetLayout();

template <class... Args>
TVertexObject<Args...>::TVertexObject()
	: CTransformable(),
	drawType_(GL_TRIANGLES)
{
}

template <class... Args>
TVertexObject<Args...>::TVertexObject(TVertexObject &&other)
	: CTransformable(std::move(other)),
	vertices_(std::move(other.vertices_)),
	drawType_(std::move(other.drawType_)),
	vBuffer_(std::move(other.vBuffer_)),
	iBuffer_(std::move(other.iBuffer_)),
	vArray_(std::move(other.vArray_))
{
}

template <class... Args>
TVertexObject<Args...>::TVertexObject(const TVertexObject &other)
	: CTransformable(other),
	vertices_(other.vertices_),
	drawType_(other.drawType_),
	vbUpdate_(true),
	ibUpdate_(true)
{
}

template <class... Args>
void TVertexObject<Args...>::addVertex(Args&&... args)
{
	vbUpdate_ = true;

	vertices_.push_back(std::forward<Args>(args)...);
}

template <class... Args>
template <std::uint64_t I>
auto& TVertexObject<Args...>::getVertexAttribute(const std::uint64_t index)
{
	vbUpdate_ = true;

	return vertices_.get<I>(index);
}

template <class... Args>
template <std::uint64_t I>
const auto& TVertexObject<Args...>::getVertexAttribute(const std::uint64_t index) const
{
	return vertices_.get<I>(index);
}

template <class... Args>
TTupleBuffer<Args...>& TVertexObject<Args...>::getVertices()
{
	return vertices_;
}

template <class... Args>
const TTupleBuffer<Args...>& TVertexObject<Args...>::getVertices() const
{
	return vertices_;
}

template <class... Args>
void TVertexObject<Args...>::setVertices(const TTupleBuffer<Args...> &vertices)
{
	vbUpdate_ = true;
	vertices_ = vertices;
}

template <class... Args>
template <std::size_t I, class T>
void TVertexObject<Args...>::setVertices(const std::vector<T> &vertices)
{
	setVertices<I>(vertices.data(), vertices.size());
}

template <class... Args>
template <std::size_t I, class T>
void TVertexObject<Args...>::setVertices(T const * const vertices, const std::uint64_t count)
{
	vbUpdate_ = true;

	if (count != vertices_.getCount())
		vertices_.resize(count);

	for (std::uint64_t i = 0u; i < count; i++)
		vertices_.get<I>(i) = *(vertices + i);
}

template <class... Args>
void TVertexObject<Args...>::setIndices(const std::vector<std::uint32_t> &indices)
{
	ibUpdate_ = true;
	indices_ = indices;
}

template <class... Args>
void TVertexObject<Args...>::setIndices(std::uint32_t const * const indices, const std::uint64_t count)
{
	ibUpdate_ = true;

	indices_.resize(count);

	for (std::uint64_t i = 0u; i < count; i++)
		indices_[i] = *(indices + i);
}

template <class... Args>
std::uint64_t TVertexObject<Args...>::getDrawType() const
{
	return drawType_;
}

template <class... Args>
void TVertexObject<Args...>::setDrawType(const std::uint64_t drawType)
{
	drawType_ = drawType;
}

template <class... Args>
CVertexLayout TVertexObject<Args...>::GetLayout()
{
	CVertexLayout result;
	GetLayout_impl(result);

	return result;
}

template <class... Args>
template <std::size_t I>
void TVertexObject<Args...>::GetLayout_impl(CVertexLayout &result)
{
	using type = std::tuple_element_t<I, std::tuple<Args...>>;

	result.addElement<type>();

	if constexpr (I + 1u < sizeof...(Args))
		GetLayout_impl<I + 1u>(result);
}

template <class... Args>
void TVertexObject<Args...>::draw(const CRenderer &renderer) const
{
	if (vbUpdate_)
		updateVBuffer();

	if (ibUpdate_)
		updateIBuffer();

	if (ibUpdate_ || vbUpdate_)
		updateVArray();

	if(vArray_.isCreated())
		renderer.draw(vArray_, drawType_);
}

template <class... Args>
void TVertexObject<Args...>::updateIBuffer() const
{
	if (!indices_.empty())
		iBuffer_.allocate(indices_.data(), indices_.size());
}

template <class... Args>
void TVertexObject<Args...>::updateVBuffer() const
{
	if(vertices_.getCount() != 0u)
		vBuffer_.allocate(vertices_.getData(), vertices_.getSize(), vertices_.getCount());
}

template <class... Args>
void TVertexObject<Args...>::updateVArray() const
{
	vArray_.setBuffer(vBuffer_, Layout_, iBuffer_);

	vbUpdate_ = false;
	ibUpdate_ = false;
}