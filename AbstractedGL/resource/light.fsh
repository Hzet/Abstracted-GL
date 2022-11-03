#version 420 core

#define LIGHT_COUNT 30

in vec3 vpos;
in vec4 vcolor;
in vec3 vnormal;
in vec2 vtexure;
in vec3 camera_position;

out vec4 out_vcolor;

struct agl_material
{
	float shininess;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
};

struct agl_spot_light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 color;
	vec3 position;
	vec3 forward;
	vec3 right;
	vec3 up;
	vec3 range;
	vec2 cut_off;
};

uniform agl_spot_light spot_light[LIGHT_COUNT];
uniform int	spot_light_active_count;
uniform agl_material material;

vec4 calculate_spot_light(agl_spot_light light, vec3 view_direction);

void main()
{
	vec3 view_direction = normalize(camera_position - vpos);

	out_vcolor = vec4(0.0);

	for(int i = 0; i < spot_light_active_count; i++)
		out_vcolor += calculate_spot_light(spot_light[i], view_direction);
}

vec4 calculate_spot_light(agl_spot_light light, vec3 view_direction)
{
	// common
	vec3 light_direction = normalize(light.position - vpos);
	vec3 reflect_direction = reflect(-light_direction, vnormal);

	// ambient
	vec4 ambient = light.color * material.ambient;

	// diffuse
	float diff = max(dot(vnormal, light_direction), 0.0);
	vec4 diffuse = light.color * (diff * material.diffuse);

	// specular
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
	vec4 specular = light.color * (spec * material.specular);

	// final color
	vec4 result = ambient + diffuse + specular;
	return result;
}