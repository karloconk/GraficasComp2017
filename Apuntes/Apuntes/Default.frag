#version 330

in vec3 InterpolatedColor;
in vec3 InterpolatedNormal;
in vec3 pixelPosition;

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 CameraPosition;

out vec4 FragColor;

void main()
{
    vec3 ambient = 0.1f * LightColor;
	vec3 L = normalize(LightPosition - pixelPosition);
	vec3 R = normalize(reflect(-L,normalize(InterpolatedNormal)));
	vec3 V = normalize(CameraPosition-pixelPosition);

	vec3 diffuse = max(dot(normalize(InterpolatedNormal), L),0.0f) * LightColor;
	vec3 specular = 0.5f * pow(max(dot(V, R),0.0f),256) * LightColor;
	vec3 phong = (ambient+diffuse+specular) * InterpolatedColor;
	FragColor = vec4(phong, 1.0f);
}

//referencias de las funciones utilizadas
//http://www.shaderific.com/glsl-functions/
