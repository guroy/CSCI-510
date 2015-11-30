#version 120

// Flat shading fragment shader

// Material properties of the teapot and torus
uniform vec4 ambient_color;
uniform float ambient_reflection_coefficient;
uniform vec4 diffuse_color;
uniform float diffuse_reflection_coefficient;

// Properties of the light source
uniform vec4 lightSourceColor;

// Properties of the ambient light
uniform vec4 ambientLightColor;

in vec3 vNorm;
in vec3 light;
in vec3 vPos;

void main()
{
	vec3 N = normalize(vNorm);
	vec3 L = normalize(light - vPos);

	// ambient
	vec4 ambient = ambient_color * ambient_reflection_coefficient * ambientLightColor;

	// diffuse
	vec4 diffuse = diffuse_color * diffuse_reflection_coefficient * (dot(N, L));
	// the vectors have been normalized so we can replace cos by dot

	gl_FragColor = ambient + diffuse * lightSourceColor;
}
