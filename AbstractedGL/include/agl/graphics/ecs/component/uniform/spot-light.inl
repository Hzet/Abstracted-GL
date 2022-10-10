uniform<spot_light>::uniform()
{
	set_name("spot_light");
}

void uniform<spot_light>::send(const shader &s, const entity &e)
{
	s.set_uniform(get_name() + "ambient", this->data.ambient);
	s.set_uniform(get_name() + "color", this->data.color);
	s.set_uniform(get_name() + "cutOff", this->data.cutOff);
	s.set_uniform(get_name() + "diffuse", this->data.diffuse);
	s.set_uniform(get_name() + "direction", this->data.direction);
	s.set_uniform(get_name() + "range", this->data.range);
	s.set_uniform(get_name() + "specular", this->data.specular);
}