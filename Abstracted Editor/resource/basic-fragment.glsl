#version 430 core

struct agl_texture_material
{
	sampler2D ambient;
};

uniform agl_texture_material texture_material;

in vec4 vcolor;
in vec2 vtexture;

out vec4 fragment_color;

void main()
{
	fragment_color = vcolor * texture(texture_material.ambient, vtexture);
} 