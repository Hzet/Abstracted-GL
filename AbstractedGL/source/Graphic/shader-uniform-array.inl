/*
template <typename T>
CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::CUniformArray()
	: shaderUID_(CShaderUID::InvalidValue())
{
}

template <typename T>
void CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::setName(const std::string &name)
{
	IUniform::setName(name);

	updateDictionary();
}

template <typename T>
const CShaderUID& CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::getShader() const
{
	return shaderUID_;
}

template <typename T>
void CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::create(const std::string &name, const CShaderUID &shaderUID)
{
	setName(name);
	shaderUID_ = shaderUID;
}

template <typename T>
void CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::redirect(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename T>
void CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::passToShader() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();

	if (lastCount_ != this->count())
	{
		updateDictionary();
		lastCount_ = this->count();
	}

	auto it = dictionary_.cbegin();
	for (const auto &v : (*this))
		shader.setUniform(*(it++), v);
}

template <typename T>
std::unique_ptr<IUniform> CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::clone() const
{
	return std::unique_ptr<IUniform>(new CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>(*this));
}

template <typename T>
void CUniformArray<T, detail::is_not_agl_uniform_concrete_t<T>>::updateDictionary() const
{
	dictionary_.resize(this->count());

	std::string elemName = this->getName() + "[ ]";
	const std::uint64_t insert = this->getName().size();

	for (std::uint64_t i = 0u; i < this->count(); i++)
	{
		const std::string num = std::to_string(i);
		elemName.replace(insert, num.size(), num);
		dictionary_[i] = elemName;
	}
}

//

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>::setName(const std::string &name)
{
	IUniform::setName(name);

	updateUniforms();
}

template <typename T>
const CShaderUID& CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>::getShaderOf(const std::string &name, std::uint64_t index) const
{
	return (*this)[index].getShaderOf(name);
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>::redirect(const std::string &name, std::uint64_t index, const CShaderUID &shaderUID)
{
	(*this)[index].redirect(name, shaderUID);
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>::passToShader() const
{
	if (lastCount_ != this->count())
	{
		updateUniforms();
		lastCount_ = this->count();
	}

	for (const auto &v : (*this))
		v.passToShader();
}

template <typename T>
std::unique_ptr<IUniform> CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>::clone() const
{
	return std::unique_ptr<IUniform>(new CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>(*this));
}

template <typename T>
void CUniformArray<T, detail::is_agl_uniform_concrete_t<T>>::updateUniforms() const
{
	std::string elemName = this->getName() + "[ ]";
	const std::uint64_t insert = this->getName().size();

	for (std::uint64_t i = 0u; i < this->count(); i++)
	{
		const std::string num = std::to_string(i);
		elemName.replace(insert, num.size(), num);
		(*this)[i].setName(elemName);
	}
}*/