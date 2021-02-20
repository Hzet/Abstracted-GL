#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;

uniform mat4 agl_camera_projection;
uniform mat4 agl_camera_view;
uniform mat4 agl_model_transform;
uniform mat4 agl_model_inverse_transform;

out vec3 vPos;
out vec4 vColor;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
	vec4 pos = agl_model_transform * vec4(aPos, 1.f);

	vPos = vec3(pos);
	vColor = aColor;
	vNormal = normalize(mat3(transpose(agl_model_inverse_transform)) * aNormal);
	vTexCoord = aTexCoord;

	gl_Position = agl_camera_projection * agl_camera_view * pos;
}