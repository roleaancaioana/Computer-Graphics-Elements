#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Clock;
uniform int Collide;
uniform int Color;

out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_color;
out vec2 frag_texture_coord;

void main()
{
	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture_coord = v_texture_coord;

	//negru
	if (Color == 0) {
		frag_color = vec3(0, 0, 0);
	}

	//rosu
	if (Color == 1) {
		frag_color = vec3(1, 0, 0);
	}

	//galben
	if (Color == 2) {
		frag_color = vec3(1, 1, 0);
	}

	//portocaliu
	if (Color == 3) {
		frag_color = vec3(1, 0.3667f, 0);
	}

	//verde
	if (Color == 4) {
		frag_color = vec3(0.6f, 1, 0);
	}

	//albastru
	if (Color == 5) {
		frag_color = vec3(0, 0, 1);
	}

	// roz
	if (Color == 6) {
		frag_color = vec3(1, 0, 0.466f);
	}

	// bleu
	if (Color == 7) {
		frag_color = vec3(0.702, 0.9, 0.886f);
	}


	if (Collide == 1) {
		frag_color = vec3(0.7667f, 0, 1);
	}

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}