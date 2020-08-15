#version 330 core
out vec4 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};  
uniform Material material; 

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  
vec3 CalcSpotLight(SpotLight spotLight, vec3 norm,vec3 FragPos,vec3 viewDir);

void main(){
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = CalcDirLight(dirLight,normal,viewDir);
	for(int i = 0 ; i < NR_POINT_LIGHTS ; i ++){
		result += CalcPointLight(pointLights[i],normal,FragPos,viewDir);
	}
	result += CalcSpotLight(spotLight, normal, FragPos, viewDir);

	color = vec4(result,1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = -normalize(light.direction);
	float diff = max(dot(lightDir,normal),0.0f);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
	vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position-fragPos);
	//ambient
	float diff = max(dot(lightDir,normal),0.0f);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow( max(dot(reflectDir,viewDir),0.0f),material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f /(light.constant + light.linear*distance + light.quadratic * distance*distance);

	return ambient + (diffuse+specular)*attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal,vec3 fragPos,vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir,-normalize(light.direction));
	float tmp1 = spotLight.cutOff - spotLight.outerCutOff ;
	float intensity = clamp( (theta-spotLight.outerCutOff)/ theta , 0, 1);

	float diff = max(dot(lightDir,normal),0.0f);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow( max(dot(reflectDir,viewDir),0.0f),material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

	float distance = length(light.position - fragPos);
	float attenuation = 1.0f /(light.constant + light.linear*distance + light.quadratic * distance*distance);

	return ambient + (diffuse+specular)*attenuation * intensity;



}