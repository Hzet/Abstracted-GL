#version 430 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texture;

struct agl_model
{
	mat4 transform;
};

struct agl_camera
{
	mat4 projection;
	mat4 view;
};

uniform agl_camera camera;
uniform agl_model model;

out vec4 vcolor;
out vec2 vtexture;

void main()
{
	vcolor = color;
	vtexture = texture;

	gl_Position = camera.projection * camera.view * model.transform * vec4(pos, 1.f);
}