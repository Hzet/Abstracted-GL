#version 420 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texture;

struct agl_model
{
	mat4 transform;
	mat4 inverse_transform;
};

struct agl_camera
{
	vec3 position;
	mat4 projection;
	mat4 view;
};

uniform agl_model model;
uniform agl_camera camera;

out vec3 vpos;
out vec4 vcolor;
out vec3 vnormal;
out vec2 vtexture;
out vec3 camera_position;

void main()
{
	vec4 position = model.transform * vec4(pos, 1.f);

	vpos = vec3(pos);
	vnormal = normalize(mat3(transpose(model.inverse_transform)) * normal);
	vtexture = texture;
	camera_position = camera.position;

	gl_Position = camera.projection * camera.view * position;
}