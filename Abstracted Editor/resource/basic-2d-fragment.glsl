#version 430 core

uniform sampler2D id_texture;

in vec4 vcolor;
in vec2 vtexture;

out vec4 fragment_color;

void main()
{
	fragment_color = vcolor;
	fragment_color *= texture(id_texture, vtexture);
}