#type vertex
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_NormalCoord;
layout(location = 3) in vec3 a_Tangent;

uniform mat4 u_ProgView;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main() {
	gl_Position = u_ProgView * u_Model * vec4(a_Position, 1.0);
	v_TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 a_Color;

uniform sampler2D u_Texture;

in vec2 v_TexCoord;

void main() {
	a_Color = texture2D(u_Texture, v_TexCoord);
}