#type vertex
#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main(){
	v_TexCoord = a_TexCoord;
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0, 1.0);
}

#type fragment
#version 460 core
layout(location = 0) out vec4 a_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
    a_Color = texture(u_Texture, v_TexCoord);
}