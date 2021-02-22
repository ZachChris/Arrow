#type vertex
#version 460 core

layout(location = 0) in vec3 a_TexCoord;

uniform mat4 u_Prog;
uniform mat4 u_View;

out vec3 v_TexCoord;

void main(){
	v_TexCoord = a_TexCoord;
	vec4 pos = u_Prog * u_View * vec4(a_TexCoord, 1.0);
	gl_Position= pos.xyww;
}

#type fragment
#version 460 core
layout(location = 0) out vec4 a_Color;

in vec3 v_TexCoord;

uniform samplerCube u_Skybox;

void main() {
    a_Color = texture(u_Skybox, v_TexCoord);
}