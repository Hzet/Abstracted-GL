uniform<material>::uniform()
{
	set_name("material");
}

void uniform<material>::send(const shader &s, const entity &e)
{
	s.set_uniform(get_name() + "shininess", this->data.shininess);
	s.set_uniform(get_name() + "ambient", this->data.ambient);
	s.set_uniform(get_name() + "diffuse", this->data.diffuse);
	s.set_uniform(get_name() + "specular", this->data.specular);
	s.set_uniform(get_name() + "emission", this->data.emission);
}