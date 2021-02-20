template <class T>
void CUniformManager::pass(const std::string &name, T value) const
{
	const CShader &shader = CShaderManager::GetShader(entries_.at(name));
	shader.setActive();
	shader.setUniform(name, value);
}