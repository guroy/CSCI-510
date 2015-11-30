#version 120

// Flat shading fragment shader

// Material properties of the teapot and torus
in vec4 Ia;
in float ka;
in vec4 Id;
in float kd;

// Properties of the light source
in vec4 lColor;
in vec4 lPosition;

// Properties of the ambient light
in vec4 lAmbient;

in vec3 vNorm;
in vec3 light;
in vec3 vPos;

void main()
{
	vec3 N = normalize(vNorm);
	vec3 L = normalize(light - vPos);

	// ambient
	vec4 ambient = Ia * ka * lAmbient;

	// diffuse
	vec4 diffuse = lColor * Id * kd * dot(N, L);
	// the vectors have been normalized so we can replace cos by dot

	gl_FragColor = ambient + diffuse;
}
