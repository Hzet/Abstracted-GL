#version 420 core

struct agl_texture_material
{
	sampler2D ambient;
	sampler2D diffuse;
	sampler2D specular;
};

struct agl_directional_light
{
	vec3 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 color;
};

struct agl_spot_light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 color;
	vec3 position;
	vec3 direction;
	vec3 range;
	vec2 cut_off;
};

vec4 calculate_directional_light(agl_directional_light light, vec3 view_direction);
vec4 calculate_spot_light(agl_spot_light light, vec3 view_direction);

in vec3 vpos;
in vec3 vnormal;
in vec2 vtexure;

out vec4 vcolor;

#define LIGHT_COUNT 30

uniform agl_directional_light directional_light;
uniform agl_spot_light spot_light[LIGHT_COUNT];
uniform int	spot_light_active_count;
uniform vec3 light_consumer_position;
uniform agl_texture_material texture_material;

void main()
{
	vec3 view_direction = normalize(light_consumer.position - vpos);

	vec4 result = calculate_directional_light(directional_light, view_direction);

	for(int i = 0; i < spot_light_active_count; i++)
		result += calculate_spot_light(spot_light[i], view_direction);

	fColor = result;
}

vec4 calculate_directional_light(SDirLight light, vec3 view_direction)
{
	vec3 light_direction = normalize(-light.direction);
	vec3 reflect_direction = reflect(-light_direction, vnormal);

	float diff = max(dot(vnormal, light_direction), 0.f);
	float spec = max(dot(view_direction, reflect_direction), 0.f);

	vec4 ambient = light.ambient * texture(texture_material.ambient, vtexture);
	vec4 diffuse = light.diffuse * diff * texture(texture_material.diffuse, vtexture);
	vec4 specular = light.specular * spec * texture(texture_material.specular, vtexture);

	return (ambient + diffuse + specular) * light.color;
}

vec4 calculate_spot_light(spot_light light, vec3 view_direction)
{
	vec3 light_direction = normalize(light.position - vpos);
	vec3 reflect_direction = reflect(-light_direction, vnormal);

	float diff = max(dot(vnormal, light_direction), 0.f);
	float spec = max(dot(view_direction, reflect_direction), 0.f);

	vec4 ambient = light.ambient * texture(texture_material.ambient, vtexture);
	vec4 diffuse = light.diffuse * diff * texture(texture_material.diffuse, vtexture);
	vec4 specular = light.specular * spec * texture(texture_material.specular, vtexture);

	float theta = dot(light_direction, normalize(-light.direction));
	float epsilon = light.cut_off.x - light.cut_off.y;

	float intensity = clamp((theta - light.cut_off.y) / epsilon, 0.f, 1.f);
	diffuse *= intensity;
	specular *= intensity;
	
	float distance = length(light.position - vpos);
	float attenuation = 1.f / (light.range.x + light.range.y * distance + light.range.z * distance * distance);

	return (ambient + diffuse + specular) * attenuation * light.color;
}