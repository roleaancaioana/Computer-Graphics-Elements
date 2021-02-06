#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int Color;

// TODO: output values to fragment shader
out vec2 frag_texture_coord;
out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
	// TODO: send output to fragment shader
	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture_coord = v_texture_coord;
	frag_color = vec3(0.55, 0.05, 0.154);


	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	
}
