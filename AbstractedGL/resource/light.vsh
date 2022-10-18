#version 420 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

struct agl_model
{
	mat4 transform;
	mat4 inverse_transform;
};

struct agl_camera
{
	mat4 projection;
	mat4 view;
};

uniform agl_model model;
uniform agl_camera camera;

out vec3 vpos;
out vec3 vnormal;
out vec2 vtexture;

void main()
{
	vec4 position = model.transform * vec4(pos, 1.f);

	vpos = vec3(pos);
	vnormal = normalize(mat3(transpose(model.inverse_transform)) * normal);
	vtexture = texture;

	gl_Position = model.transform * camera.projection * camera.view * vec4(pos, 1.f);
}