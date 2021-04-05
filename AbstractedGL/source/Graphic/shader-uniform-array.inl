template <typename T>
TUniformArray<T, detail::is_agl_uniform_t<T>>::TUniformArray(const std::string &name, IUniform const * const parent /*= nullptr*/)
	: IUniform(name, parent),
	lastCount_(0u)
{
}

template <typename T>
void TUniformArray<T, detail::is_agl_uniform_t<T>>::passUniform() const
{
	for (auto it = this->cbegin(); it != this->cend(); ++it)
		it->passUniform();
}

template <typename T>
void TUniformArray<T, detail::is_agl_uniform_t<T>>::setIndex(std::uint64_t index)
{
	IUniform::setIndex(index);

	for (auto it = this->begin(); it != this->end(); ++it)
		it->updateNamespace(this->getFullName());
}

template <typename T>
void TUniformArray<T, detail::is_agl_uniform_t<T>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;

	for (auto it = this->begin(); it != this->end(); ++it)
		it->setShader(shaderUID);
}

template <typename T>
void TUniformArray<T, detail::is_agl_uniform_t<T>>::updateNamespace(const std::string &name)
{
	IUniform::updateNamespace(name);

	for (auto it = this->begin(); it != this->end(); ++it)
		it->updateNamespace(this->getFullName());
}

template <typename T>
void TUniformArray<T, detail::is_agl_uniform_t<T>>::onUpdate()
{
	std::uint64_t i = 0u;
	for (auto it = this->begin(); it != this->end(); ++it, i++)
	{
		it->setIndex(i);
		it->setShader(shaderUID_);
		it->setFullName(this->getFullName() + it->getName());
	}
}

template <typename T>
std::unique_ptr<IUniform> TUniformArray<T, detail::is_agl_uniform_t<T>>::clone() const
{
	return std::unique_ptr<IUniform>(new TUniformArray<T>(*this));
}