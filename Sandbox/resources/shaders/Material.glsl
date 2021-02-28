#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_NormalCoord;
layout(location = 3) in vec3 a_Tangent;

uniform mat4 u_ProgView;
uniform mat4 u_Model;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;
out mat3 v_TBN;

void main(){
	mat3 model = transpose(inverse(mat3(u_Model)));
	vec3 T = normalize(model * a_Tangent);
	vec3 N = normalize(model * a_NormalCoord);
	T = normalize(T - dot(T, N) * N);
	vec3 B =  cross(N, T);

	v_TBN = mat3(T, B, N);

	gl_Position = u_ProgView * u_Model * vec4(a_Position, 1.0);
	v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
	v_Normal = mat3(u_Model) * a_NormalCoord;
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 460 core
layout(location = 0) out vec4 a_Color;

struct DirectionalLight {
	vec3 Direction;
	vec3 Color;
};

struct PointLight{
	vec3 Position;
	vec3 Color;
	
    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight {
	vec3 Position;
	vec3 Direction;
	vec3 Color;

	float CutOff;

	float Constant;
    float Linear;
    float Quadratic;

};

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;
in mat3 v_TBN;

uniform vec3 u_ViewPos;

uniform PointLight u_PointLight;
//uniform SpotLight u_SpotLight;

uniform sampler2D u_Texture;
uniform sampler2D u_NormalMap;
uniform sampler2D u_Specular;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDir = normalize(-light.Direction);
	vec3 halfwayDir = normalize(lightDir + viewDirection);

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.Color * vec3(texture(u_Texture, v_TexCoord));

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.Color * vec3(texture(u_Texture, v_TexCoord));

	float specularStrength = 0.5;
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.Color * vec3(texture(u_Specular, v_TexCoord));  

	return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDir = normalize(light.Position - v_FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDirection);

	float distance = length(light.Position - v_FragPos);

	float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.Color * vec3(texture(u_Texture, v_TexCoord)) * attenuation;

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.Color * vec3(texture(u_Texture, v_TexCoord)) * attenuation;
  
	vec3 reflectDir = reflect(-lightDir, normal);

	float specularStrength = 0.5;
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.Color * vec3(texture(u_Specular, v_TexCoord)) * attenuation;  

	return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 viewDirection) {
	vec3 result;

	vec3 lightDir = normalize(light.Position - v_FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDirection);

	float distance = length(light.Position - v_FragPos);

	float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.Color * vec3(texture(u_Texture, v_TexCoord)) * attenuation;

	float theta = dot(lightDir, normalize(-light.Direction));

	if(theta > light.CutOff) {
		float diff = max(dot(normal, lightDir), 0.0);
		vec3 diffuse = diff * light.Color * vec3(texture(u_Texture, v_TexCoord)) * attenuation;
  
		float specularStrength = 0.5;
		vec3 reflectDir = reflect(-lightDir, normal);

		float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
		vec3 specular = specularStrength * spec * light.Color * vec3(texture(u_Specular, v_TexCoord)) * attenuation;  

		result = ambient + diffuse + specular;
	} else
		result = ambient;

	return result;
}

void main() {
	//vec3 normal = texture2D(u_NormalMap, v_TexCoord).xyz;
	//normal = 255.0/128.0 * normal - 1;
	//normal = v_TBN * normal;
	vec3 normal = normalize(v_Normal);

	vec3 viewDir = normalize(u_ViewPos - v_FragPos);

	vec3 result = CalculatePointLight(u_PointLight, normal, viewDir);
	//result += CalculateSpotLight(u_SpotLight, normal, viewDir);
	a_Color = vec4(result, 1.0);
}