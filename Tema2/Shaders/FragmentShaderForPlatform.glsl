#version 330

in vec2 frag_texture_coord;
in vec3 frag_color;
in vec3 frag_normal;

uniform sampler2D texture_1;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

void main() {
	out_normal = vec4(frag_normal, 1);
	vec4 color = texture2D(texture_1, frag_texture_coord);

	if (color.a < 0.5f) {
		discard;
	}

	out_color = color * vec4(frag_color, 1);
}