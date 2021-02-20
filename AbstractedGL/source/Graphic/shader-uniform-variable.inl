template <class T>
void IUniformVariable::passValue(const std::string &name, T value) const
{
	const CShader &shader = CShaderManager::GetShader(uniformManager_.getShaderOf(getName() + name));
	shader.setActive();
	shader.setUniform(getName() + name, value);
}