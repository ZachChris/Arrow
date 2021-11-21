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
	mat3 modelVector = transpose(inverse(mat3(u_Model)));

	vec3 T = normalize(vec3(u_Model * vec4(a_Tangent, 0.0)));
	vec3 N = normalize(vec3(u_Model * vec4(a_NormalCoord, 0.0)));
	vec3 B = cross(N, T);
	
	v_TBN = transpose(mat3(T, B, N));
	v_TexCoord = a_TexCoord;
	gl_Position = u_ProgView * u_Model * vec4(a_Position, 1.0);
	v_FragPos = vec3(u_Model * vec4(a_Position, 1.0f));
	v_Normal = mat3(transpose(inverse(u_Model))) * a_NormalCoord;
}

#type fragment
#version 460 core
layout(location = 0) out vec4 a_Color;

struct PointLight{
	vec3 Position;
	vec3 Color;
	
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

uniform vec4 u_Color;

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDirection) {
	vec3 lightDir = normalize(light.Position - v_FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDirection);

	float distance = length(light.Position - v_FragPos);

	float attenuation = 1.0 / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.Color * vec3(u_Color) * attenuation;

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.Color * vec3(u_Color) * attenuation;
  
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float specularStrength = 0.5;
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.Color * attenuation;  

	return ambient + diffuse + specular;
}

void main() {
   vec3 normal = normalize(v_Normal);
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);

	vec3 result = CalculatePointLight(u_PointLight, normal, viewDir);

	a_Color = u_Color;
}