#version 430 core

in vec4 vcolor;

out vec4 fragment_color;

void main()
{
    fragment_color = vcolor;
} 