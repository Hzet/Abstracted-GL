#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 vtexture;

struct agl_camera 
{
	mat4 projection;
	mat4 view;
};

struct agl_model
{
	mat4 transform;
};

uniform agl_camera camera;
uniform agl_model model;

void main()
{
	vtexture = texture;

	gl_Position = camera.projection * camera.view * vec4(position.x / 800, position.y / 900, position.z, 1.0);
}