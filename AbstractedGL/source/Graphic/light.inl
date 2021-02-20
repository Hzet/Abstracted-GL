
template <class... Args>
CLight<Args...>::CLight()
{
	this->setShader(Shader::BASIC_SHADER);
	this->redirectUniform("agl_model_transform", Shader::BASIC_SHADER);
	spotLight.setName("agl_light_point");
	spotLight.create(".position", Shader::LIGHT_SHADER);
}

template <class... Args>
CLight<Args...>::CLight(CLight &&other)
	: CMesh<Args...>(std::move(other)),
	spotLight(std::move(other.spotLight))
{
}

template <class... Args>
CLight<Args...>::CLight(const CLight &other)
	: CMesh<Args...>(other),
	spotLight(other.spotLight)
{
}

template <class... Args>
void CLight<Args...>::draw(const CRenderer &renderer) const
{
	spotLight.passToShader();
	spotLight.passValue(".position", this->getPosition());

	CMesh<Args...>::draw(renderer);
}
