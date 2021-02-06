#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_color;

uniform int Color;
uniform mat4 Model;

out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
	frag_position = v_position;
	frag_normal = v_normal;

	if (Color == 7) {
		frag_color = vec3(1, 1, 1);
	};

	if (Color == 8) {
		frag_color = vec3(0, 0.4333f, 1);
	}

	gl_Position = Model * vec4(v_position, 1.0);
}