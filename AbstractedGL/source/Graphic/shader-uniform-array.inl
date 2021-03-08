template <typename T>
CUniformArray<T, detail::is_agl_uniform_t<T>>::CUniformArray(const std::string &name, IUniform const * const parent /*= nullptr*/)
	: IUniform(name, parent),
	lastCount_(0u)
{
}

template <typename T>
CUniformArray<T, detail::is_agl_uniform_t<T>>::CUniformArray(CUniformArray<T, detail::is_agl_uniform_t<T>> &&other)
	: IUniform(std::move(other)),
	CInheritableVector<T>(std::move(other)),
	lastCount_(0u)
{
}

template <typename T>
CUniformArray<T, detail::is_agl_uniform_t<T>>::CUniformArray(const CUniformArray &other)
	: IUniform(other),
	CInheritableVector<T>(other),
	lastCount_(0u)
{
}

template <typename T>
CUniformArray<T, detail::is_agl_uniform_t<T>>::CUniformArray(const CUniformArray &other, IUniform const * const parent)
	: IUniform(other, parent),
	CInheritableVector<T>(other),
	lastCount_(0u)
{
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_t<T>>::passUniform() const
{
	if (lastCount_ != this->count())
	{
		for (std::uint64_t i = 0u; i < this->count(); i++)
			(*this)[i].setIndex(i);
		lastCount_ = this->count();
	}

	for (auto it = this->cbegin(); it != this->cend(); ++it)
		it->passUniform();
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_t<T>>::setIndex(std::uint64_t index)
{
	IUniform::setIndex(index);

	for (std::uint64_t i = 0u; i < this->count(); i++)
		(*this)[i].setIndex(i);
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_t<T>>::setShader(const CShaderUID &shaderUID)
{
	for (auto it = this->cbegin(); it != this->cend(); ++it)
		it->setShader(shaderUID);
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_t<T>>::updateNamespace(const std::string &name)
{
	IUniform::updateNamespace(name);

	for (auto it = this->cbegin(); it != this->cend(); ++it)
		it->updateNamespace(this->getFullName());
}