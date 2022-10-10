#version 430 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

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

void main()
{
	vcolor = color;

	gl_Position = camera.projection * camera.view * model.transform * vec4(pos, 1.f);
}