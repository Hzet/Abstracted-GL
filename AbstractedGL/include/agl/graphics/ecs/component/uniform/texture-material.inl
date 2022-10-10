uniform<texture>::uniform()
{
	set_name("texture");
}

void uniform<texture>::send(const shader &s, const entity &e)
{
	auto i = 0;

	if (bindTexture(this->data.ambient))
		s.set_uniform(get_name() + "ambient", i++);

	if (bindTexture(this->data.diffuse))
		s.set_uniform(get_name() + "diffuse", i++);

	if (bindTexture(this->data.specular))
		s.set_uniform(get_name() + "specular", i++);
}

bool uniform<texture>::bindTexture(const texture_uid &id_texture_2d)
{
	if (!texture_atlas::has_texture_2d(id_texture_2d))
		return false;

	texture_atlas::get_texture(id_texture_2d).bind();
	return true;
}