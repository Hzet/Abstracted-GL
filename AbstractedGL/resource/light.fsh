#version 430 core

struct STextureMaterial
{
	float shininess;
	sampler2D diffuse;
	sampler2D specular;
};

struct SDirLight
{
	vec3 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 color;
};

struct SPointLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 color;

	vec3 position;
	vec3 direction;

	vec3 range;

	vec2 cutOff;
};

vec4 getDirLight(SDirLight light, vec3 normal, vec3 viewDirection);
vec4 getPointLight(SPointLight light, vec3 normal, vec3 vpos, vec3 viewDirection);

in vec3 vPos;
in vec4 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fColor;

#define LIGHT_COUNT 30

uniform SDirLight        agl_directional_light;
uniform SPointLight      agl_light_point[LIGHT_COUNT];
uniform vec3             agl_light_consumer_position;
uniform STextureMaterial agl_texture_material;

void main()
{
	vec3 viewDirection = normalize(agl_light_consumer_position - vPos);

	vec4 result = getDirLight(agl_directional_light, viewDirection);

	//for(int i = 0; i < LIGHT_COUNT; i++)
		//result += getPointLight(agl_light_point[i], viewDirection);
	
	result += getPointLight(agl_light_point[0], viewDirection);

	fColor = result * vColor;
}

vec4 getDirLight(SDirLight light, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);
	vec3 reflectDirection = reflect(-lightDirection, vNormal);

	float diff = max(dot(vNormal, lightDirection), 0.f);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.f), agl_texture_material.shininess * 128);

	vec4 ambient = light.ambient * texture(agl_texture_material.diffuse, vTexCoord);
	vec4 diffuse = light.diffuse * diff * texture(agl_texture_material.diffuse, vTexCoord);
	vec4 specular = light.specular * spec * texture(agl_texture_material.specular, vTexCoord);

	return (ambient + diffuse + specular) * light.color;
}

vec4 getPointLight(SPointLight light, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - vPos);
	vec3 reflectDirection = reflect(-lightDirection, vNormal);

	float diff = max(dot(vNormal, lightDirection), 0.f);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.f), agl_texture_material.shininess * 128);

	vec4 ambient = light.ambient * texture(agl_texture_material.diffuse, vTexCoord);
	vec4 diffuse = light.diffuse * diff * texture(agl_texture_material.diffuse, vTexCoord);
	vec4 specular = light.specular * spec * texture(agl_texture_material.specular, vTexCoord);

	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff.x - light.cutOff.y;

	float intensity = clamp((theta - light.cutOff.y) / epsilon, 0.f, 1.f);
	
	float distance = length(light.position - vPos);
	float attenuation = 1.f / (light.range.x + light.range.y * distance + light.range.z * distance * distance);

	return (ambient + diffuse + specular) * intensity * attenuation * light.color;
}