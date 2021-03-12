#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 agl_model_transform;
uniform mat4 agl_camera_view;
uniform mat4 agl_camera_projection;

out vec4 vColor;

void main()
{
	vColor = aColor;
	gl_Position = agl_camera_projection * agl_camera_view * agl_model_transform * vec4(aPos, 1.f);
}