
template <typename TReturn>
CUniform<TReturn>::CUniform(const std::string &name, IUniform const * const parent/* = nullptr*/, detail::TValue<TReturn> &&value/* = T()*/, const CShaderUID &shaderUID/* = CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	value_(value.value)
{
}

template <typename TReturn>
CUniform<TReturn>::CUniform(CUniform &&other)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	value_(std::move(other.value_))
{
}

template <typename TReturn>
CUniform<TReturn>::CUniform(const CUniform &other)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	value_(other.value_)
{
}

template <typename TReturn>
CUniform<TReturn>::CUniform(const CUniform &other, detail::TValue<TReturn> &&value, IUniform const * const parent /*= nullptr*/)
	: IUniform(other, parent),
	shaderUID_(other.shaderUID_),
	value_(value.value)
{
}

template <typename TReturn>
const CShaderUID& CUniform<TReturn>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn>
void CUniform<TReturn>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn>
TReturn& CUniform<TReturn>::operator()()
{
	return value_;
}

template <typename TReturn>
const TReturn& CUniform<TReturn>::operator()() const
{
	return value_;
}

template <typename TReturn>
CUniform<TReturn>::operator TReturn()
{
	return value_;
}

template <typename TReturn>
CUniform<TReturn>::operator TReturn() const
{
	return value_;
}

template <typename TReturn>
void CUniform<TReturn>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), value_);

}


template <typename TReturn, typename TObject>
CUniform<TReturn, TObject, detail::is_class_t<TObject>>::CUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent /*= nullptr*/, const CShaderUID &shaderUID /*= CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	object_(object.value),
	method_(method.value)
{
}

template <typename TReturn, typename TObject>
CUniform<TReturn, TObject, detail::is_class_t<TObject>>::CUniform(CUniform &&other)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	object_(std::move(other.object_)),
	method_(std::move(other.method_))
{
}

template <typename TReturn, typename TObject>
CUniform<TReturn, TObject, detail::is_class_t<TObject>>::CUniform(const CUniform &other)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	object_(other.object_),
	method_(other.method_)
{
}

template <typename TReturn, typename TObject>
CUniform<TReturn, TObject, detail::is_class_t<TObject>>::CUniform(const CUniform &other, detail::TValue<TObject> &&object, IUniform const * const parent /*= nullptr*/)
	: IUniform(other, parent),
	shaderUID_(other.shaderUID_),
	method_(other.method_),
	object_(object.value)
{
}



template <typename TReturn, typename TObject>
const CShaderUID& CUniform<TReturn, TObject, detail::is_class_t<TObject>>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn, typename TObject>
void CUniform<TReturn, TObject, detail::is_class_t<TObject>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn, typename TObject>
TReturn CUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator()()
{
	return static_cast<TReturn>(std::invoke(method_, object_));
}

template <typename TReturn, typename TObject>
TReturn CUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator()() const
{
	return static_cast<TReturn>(std::invoke(method_, object_));
}

template <typename TReturn, typename TObject>
CUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator TReturn()
{
	return (*this)();
}

template <typename TReturn, typename TObject>
CUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator TReturn() const
{
	return (*this)();
}

template <typename TReturn, typename TObject>
void CUniform<TReturn, TObject, detail::is_class_t<TObject>>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}


template <typename TReturn, typename TFunction>
CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::CUniform(const std::string &name, detail::TValue<TFunction> &&function, IUniform const * const parent /*= nullptr*/, const CShaderUID &shaderUID /*= CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	function_(function.value)
{
}

template <typename TReturn, typename TFunction>
CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::CUniform(CUniform &&other)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	function_(std::move(other.function_))
{
}

template <typename TReturn, typename TFunction>
CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::CUniform(const CUniform &other)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	function_(other.function_)
{
}

template <typename TReturn, typename TFunction>
CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::CUniform(const CUniform &other, IUniform const * const parent)
	: IUniform(other, parent),
	shaderUID_(other.shaderUID_),
	function_(other.function_)
{
}

template <typename TReturn, typename TFunction>
const CShaderUID& CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn, typename TFunction>
void CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn, typename TFunction>
TReturn CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator()()
{
	return std::invoke(function_);
}

template <typename TReturn, typename TFunction>
TReturn CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator()() const
{
	return std::invoke(function_);
}

template <typename TReturn, typename TFunction>
CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator TReturn()
{
	return (*this)();
}

template <typename TReturn, typename TFunction>
CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator TReturn() const
{
	return (*this)();
}

template <typename TReturn, typename TFunction>
void CUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}

template <typename TReturn, typename TObject, typename TMethod>
CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::CUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent /*= nullptr*/, const CShaderUID &shaderUID /*= CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	object_(object.value),
	method_(method.value)
{
}

template <typename TReturn, typename TObject, typename TMethod>
CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::CUniform(CUniform &&other)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	object_(std::move(other.object_)),
	method_(std::move(other.method_))
{
}

template <typename TReturn, typename TObject, typename TMethod>
CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::CUniform(const CUniform &other)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	object_(other.object_),
	method_(other.method_)
{
}

template <typename TReturn, typename TObject, typename TMethod>
CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::CUniform(const CUniform &other, detail::TValue<TObject> &&object, IUniform const * const parent /*= nullptr*/)
	: IUniform(other, parent),
	shaderUID_(other.shaderUID_),
	object_(object.value),
	method_(other.method_)
{
}

template <typename TReturn, typename TObject, typename TMethod>
const CShaderUID& CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn, typename TObject, typename TMethod>
void CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn, typename TObject, typename TMethod>
TReturn CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator()()
{
	return std::invoke(method_, object_);
}

template <typename TReturn, typename TObject, typename TMethod>
TReturn CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator()() const
{
	return std::invoke(method_, object_);
}

template <typename TReturn, typename TObject, typename TMethod>
CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator TReturn()
{
	return (*this)();
}

template <typename TReturn, typename TObject, typename TMethod>
CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator TReturn() const
{
	return (*this)();
}

template <typename TReturn, typename TObject, typename TMethod>
void CUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}