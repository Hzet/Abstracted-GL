#version 430 core

#define MAX_TEXTURE_ELEMENTS 30

struct STextureMaterial
{
	int ambient_count;
	sampler2D ambient[MAX_TEXTURE_ELEMENTS];

	int diffuse_count;
	sampler2D diffuse[MAX_TEXTURE_ELEMENTS];

	int specular_count;
	sampler2D specular[MAX_TEXTURE_ELEMENTS];
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

vec4 getDirLight(SDirLight light, vec3 viewDirection);
vec4 getPointLight(SPointLight light, vec3 viewDirection);
vec4 processTextureElement(vec4 color, sampler2D textures[MAX_TEXTURE_ELEMENTS], int count);

in vec3 vPos;
//in vec4 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fColor;

#define LIGHT_COUNT 30

uniform SDirLight        agl_directional_light;
uniform int				 agl_spot_light_count;
uniform SPointLight      agl_light_point[LIGHT_COUNT];
uniform vec3             agl_light_consumer_position;
uniform STextureMaterial agl_texture_material;

void main()
{
	vec3 viewDirection = normalize(agl_light_consumer_position - vPos);

	vec4 result = getDirLight(agl_directional_light, viewDirection);

	for(int i = 0; i < agl_spot_light_count; i++)
		result += getPointLight(agl_light_point[i], viewDirection);

	fColor = result;// * vColor;
}

vec4 getDirLight(SDirLight light, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);
	vec3 reflectDirection = reflect(-lightDirection, vNormal);

	float diff = max(dot(vNormal, lightDirection), 0.f);
	float spec = max(dot(viewDirection, reflectDirection), 0.f);

	vec4 ambient = processTextureElement(light.ambient, agl_texture_material.ambient, agl_texture_material.ambient_count);
	vec4 diffuse = processTextureElement(light.diffuse * diff, agl_texture_material.diffuse, agl_texture_material.diffuse_count);
	vec4 specular = processTextureElement(light.specular * spec, agl_texture_material.specular, agl_texture_material.specular_count);

	return (ambient + diffuse + specular) * light.color;
}

vec4 getPointLight(SPointLight light, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - vPos);
	vec3 reflectDirection = reflect(-lightDirection, vNormal);

	float diff = max(dot(vNormal, lightDirection), 0.f);
	float spec = max(dot(viewDirection, reflectDirection), 0.f);

	vec4 ambient = processTextureElement(light.ambient, agl_texture_material.ambient, agl_texture_material.ambient_count);
	vec4 diffuse = processTextureElement(light.diffuse * diff, agl_texture_material.diffuse, agl_texture_material.diffuse_count);
	vec4 specular = processTextureElement(light.specular * spec, agl_texture_material.specular, agl_texture_material.specular_count);

	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff.x - light.cutOff.y;

	float intensity = clamp((theta - light.cutOff.y) / epsilon, 0.f, 1.f);
	diffuse *= intensity;
	specular *= intensity;
	
	float distance = length(light.position - vPos);
	float attenuation = 1.f / (light.range.x + light.range.y * distance + light.range.z * distance * distance);

	return (ambient + diffuse + specular) * attenuation * light.color;
}

vec4 processTextureElement(vec4 color, sampler2D textures[MAX_TEXTURE_ELEMENTS], int count)
{
	vec4 result = vec4(0.f);
	for(int i = 0; i < count; i++)
		result += color * texture(textures[i], vTexCoord);

	return result;
}