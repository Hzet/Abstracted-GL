#version 430 core

uniform sampler2D id_texture;

in vec2 vtexture;

out vec4 fragment_color;

void main()
{
	fragment_color = vec4(1.0, 1.0, 1.0, texture(id_texture, vtexture);
}