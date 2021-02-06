#version 330

in vec3 frag_normal;
in vec3 frag_color;
in vec2 frag_texture_coord;

uniform sampler2D texture_1;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

void main() {
	out_normal = vec4(frag_normal, 1);
	vec4 color = texture2D(texture_1, frag_texture_coord);

	out_color = color;
}