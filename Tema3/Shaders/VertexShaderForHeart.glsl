#version 330

// TODO: get vertex attributes from each location

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_color;

// Uniform properties
uniform int Color;
uniform mat4 Model;

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_color;

void main()
{
	frag_position = v_position;
	if (Color == 1) {
		frag_color = vec3(1, 0, 0);
	}

	if (Color == 10) {
		frag_color = vec3(0.35f, 1, 0);
	}
	frag_normal = v_normal;

	gl_Position = Model * vec4(v_position, 1.0);
}
