
template <class... Args>
CLight<Args...>::CLight()
	: CMesh<Args...>(),
	spotLight("agl_light_point"),
	position("position", { *this }, { &CTransformable::getPosition }, &spotLight, Shader::LIGHT_SHADER)
{
	spotLight.addUniform(position);
	this->setShader(Shader::BASIC_SHADER);
	this->transform.setShader(Shader::BASIC_SHADER);
}

template <class... Args>
CLight<Args...>::CLight(CLight &&other)
	: CMesh<Args...>(std::move(other)),
	spotLight(std::move(other.spotLight)),
	position(std::move(other.position))
{
}

template <class... Args>
CLight<Args...>::CLight(const CLight &other)
	: CMesh<Args...>(other),
	spotLight(other.spotLight),
	position(other.position, { *this })
{
}

template <class... Args>
void CLight<Args...>::draw(const CRenderer &renderer) const
{
	spotLight.passUniform();

	CMesh<Args...>::draw(renderer);
}
