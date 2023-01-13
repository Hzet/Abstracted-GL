#version 430 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture;

out vec2 vtexture;

struct agl_camera 
{
	mat4 projection;
	vec2 resolution;
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
	vec2 pos = position / camera.resolution;

	gl_Position = camera.projection * camera.view * model.transform * vec4(pos, 0.0, 1.0);
}