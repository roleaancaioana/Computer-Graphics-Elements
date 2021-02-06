#version 330

// TODO: get values from fragment shader
in vec3 frag_normal;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

void main()
{
	// TODO: write pixel out color
	//Task 5
	//out_color = vec4(frag_normal, 1);
	out_color = vec4(frag_color, 1);
	out_normal = vec4(frag_normal, 1);
	
}