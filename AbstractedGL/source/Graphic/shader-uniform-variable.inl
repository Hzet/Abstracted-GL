template <typename TReturn>
TUniform<TReturn>::TUniform(const std::string &name, IUniform const * const parent/* = nullptr*/, detail::TValue<TReturn> &&value/* = T()*/, const CShaderUID &shaderUID/* = CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	value_(value.value)
{
}

template <typename TReturn>
TUniform<TReturn>::TUniform(TUniform &&other, detail::TValue<TReturn> &&value)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	value_(value.value)
{
}

template <typename TReturn>
TUniform<TReturn>::TUniform(const TUniform &other, detail::TValue<TReturn> &&value)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	value_(value.value)
{
}

template <typename TReturn>
const CShaderUID& TUniform<TReturn>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn>
void TUniform<TReturn>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn>
detail::true_type_t<TReturn>& TUniform<TReturn>::operator()()
{
	if constexpr (std::is_reference_v<TReturn>)
		return value_.get();
	
	return value_;
}

template <typename TReturn>
const detail::true_type_t<TReturn>& TUniform<TReturn>::operator()() const
{
	if constexpr (std::is_reference_v<TReturn>)
		return value_.get();

	return value_;
}

template <typename TReturn>
TUniform<TReturn>::operator detail::true_type_t<TReturn>&()
{
	if constexpr (std::is_reference_v<TReturn>)
		return value_.get();

	return value_;
}

template <typename TReturn>
TUniform<TReturn>::operator const detail::true_type_t<TReturn>&() const
{
	if constexpr (std::is_reference_v<TReturn>)
		return value_.get();

	return value_;
}

template <typename TReturn>
void TUniform<TReturn>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}

template <typename TReturn>
std::unique_ptr<IUniform> TUniform<TReturn>::clone() const
{
	return std::unique_ptr<IUniform>(new TUniform<TReturn>(*this));
}

template <typename TReturn, typename TObject>
TUniform<TReturn, TObject, detail::is_class_t<TObject>>::TUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent /*= nullptr*/, const CShaderUID &shaderUID /*= CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	object_(object.value),
	method_(method.value)
{
}

template <typename TReturn, typename TObject>
TUniform<TReturn, TObject, detail::is_class_t<TObject>>::TUniform(TUniform &&other, detail::TValue<TObject> &&object)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	method_(std::move(other.method_)),
	object_(object.value)
{
}

template <typename TReturn, typename TObject>
TUniform<TReturn, TObject, detail::is_class_t<TObject>>::TUniform(const TUniform &other, detail::TValue<TObject> &&object)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	method_(other.method_),
	object_(object.value)
{
}

template <typename TReturn, typename TObject>
const CShaderUID& TUniform<TReturn, TObject, detail::is_class_t<TObject>>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn, typename TObject>
void TUniform<TReturn, TObject, detail::is_class_t<TObject>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn, typename TObject>
TReturn TUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator()()
{
	return std::invoke(method_, object_.get());
}

template <typename TReturn, typename TObject>
TReturn TUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator()() const
{
	return std::invoke(method_, object_.get());
}

template <typename TReturn, typename TObject>
TUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator TReturn()
{
	return (*this)();
}

template <typename TReturn, typename TObject>
TUniform<TReturn, TObject, detail::is_class_t<TObject>>::operator TReturn() const
{
	return (*this)();
}

template <typename TReturn, typename TObject>
void TUniform<TReturn, TObject, detail::is_class_t<TObject>>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}

template <typename TReturn, typename TObject>
std::unique_ptr<IUniform> TUniform<TReturn, TObject, detail::is_class_t<TObject>>::clone() const
{
	return std::unique_ptr<IUniform>(new TUniform<TReturn, TObject>(*this));
}

template <typename TReturn, typename TObject, typename TMethod>
TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::TUniform(const std::string &name, detail::TValue<TObject> &&object, detail::TValue<TMethod> &&method, IUniform const * const parent /*= nullptr*/, const CShaderUID &shaderUID /*= CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	object_(object.value),
	method_(method.value)
{
}

template <typename TReturn, typename TObject, typename TMethod>
TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::TUniform(TUniform &&other, detail::TValue<TObject> &&object)
	: IUniform(std::move(other)),
	shaderUID_(std::move(other.shaderUID_)),
	object_(object.value),
	method_(std::move(other.method_))
{
}

template <typename TReturn, typename TObject, typename TMethod>
TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::TUniform(const TUniform &other, detail::TValue<TObject> &&object)
	: IUniform(other),
	shaderUID_(other.shaderUID_),
	object_(object.value),
	method_(other.method_)
{
}

template <typename TReturn, typename TObject, typename TMethod>
const CShaderUID& TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn, typename TObject, typename TMethod>
void TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn, typename TObject, typename TMethod>
TReturn TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator()()
{
	return std::invoke(method_, object_.get());
}

template <typename TReturn, typename TObject, typename TMethod>
TReturn TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator()() const
{
	return std::invoke(method_, object_.get());
}

template <typename TReturn, typename TObject, typename TMethod>
TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator TReturn()
{
	return (*this)();
}

template <typename TReturn, typename TObject, typename TMethod>
TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::operator TReturn() const
{
	return (*this)();
}

template <typename TReturn, typename TObject, typename TMethod>
void TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}

template <typename TReturn, typename TObject, typename TMethod>
std::unique_ptr<IUniform> TUniform<TReturn, TObject, TMethod, detail::is_class_method<TObject, TMethod>>::clone() const
{
	return std::unique_ptr<IUniform>(new TUniform<TReturn, TObject, TMethod>(*this));
}

template <typename TReturn, typename TFunction>
TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::TUniform(const std::string &name, detail::TValue<TFunction> &&function, IUniform const * const parent /*= nullptr*/, const CShaderUID &shaderUID /*= CShaderUID::InvalidValue{}*/)
	: IUniform(name, parent),
	shaderUID_(shaderUID),
	function_(function.value)
{
}

template <typename TReturn, typename TFunction>
const CShaderUID& TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::getShader() const
{
	return shaderUID_;
}

template <typename TReturn, typename TFunction>
void TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::setShader(const CShaderUID &shaderUID)
{
	shaderUID_ = shaderUID;
}

template <typename TReturn, typename TFunction>
TReturn TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator()()
{
	return std::invoke(function_);
}

template <typename TReturn, typename TFunction>
TReturn TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator()() const
{
	return std::invoke(function_);
}

template <typename TReturn, typename TFunction>
TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator TReturn()
{
	return (*this)();
}

template <typename TReturn, typename TFunction>
TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::operator TReturn() const
{
	return (*this)();
}

template <typename TReturn, typename TFunction>
void TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::passUniform() const
{
	const CShader &shader = CShaderManager::GetShader(shaderUID_);
	shader.setActive();
	shader.setUniform(this->getFullName(), (*this)());
}

template <typename TReturn, typename TFunction>
std::unique_ptr<IUniform> TUniform<TReturn, TFunction, detail::is_function_pointer_t<TFunction>>::clone() const
{
	return std::unique_ptr<IUniform>(new TUniform<TReturn, TFunction>(*this));
}