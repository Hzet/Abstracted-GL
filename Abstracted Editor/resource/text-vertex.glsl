#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 vtexture;

struct agl_camera 
{
	mat4 projection;
	mat4 view;
};

uniform agl_camera camera;

void main()
{
	vtexture = texture;

	gl_Position = camera.projection * camera.view * vec4(position, 1.0);
}