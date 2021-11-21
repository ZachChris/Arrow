#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_normalCoord;

uniform mat4 u_ProgView;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main(){
	v_TexCoord = a_TexCoord;
	gl_Position = u_ProgView * u_Model * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core
layout(location = 0) out vec4 a_Color;

in vec2 v_TexCoord;

void main() {
    a_Color = vec4(v_TexCoord.x, v_TexCoord.y, 0.0, 1.0);
}