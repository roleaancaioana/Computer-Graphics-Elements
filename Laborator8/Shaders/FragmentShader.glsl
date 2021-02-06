#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int isSpotlight;
uniform float angle;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = reflect(L, normalize(world_normal));
	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(N, L), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	// TODO: compute light
	vec3 light;

	float d	= distance(light_position, world_position);
	float factor = 1/(0.1 + d * 0.35 + d * d * 0.2);

	if (isSpotlight == 1) {
		float cut_off = radians(angle);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cut_off);

		float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
		float light_att_factor = pow(linear_att, 2);
		if (spot_light > cos(cut_off))
		{
			light = object_color * (ambient_light + (light_att_factor) * (diffuse_light + specular_light));
		}
		else {
			light = ambient_light * object_color;
		}

	} else {
		light = object_color * (ambient_light + factor * (diffuse_light + specular_light));
	}

	// TODO: write pixel out color
	out_color = vec4(light, 1);
}