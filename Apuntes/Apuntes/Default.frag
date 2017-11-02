#version 330

in vec3 InterpolatedColor;
in vec3 InterpolatedNormal;
in vec3 pixelPosition;
in vec2 InterpolatedTexCoord;

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 CameraPosition;
uniform sampler2D DiffuseTexture;
uniform sampler2D DiffuseTexture2;

out vec4 FragColor;

void main()
{
    vec3 ambient = 0.1f * LightColor;
	vec3 L = normalize(LightPosition - pixelPosition);
	vec3 R = normalize(reflect(-L,normalize(InterpolatedNormal)));
	vec3 V = normalize(CameraPosition-pixelPosition);

	vec3 diffuse = max(dot(normalize(InterpolatedNormal), L),0.0f) * LightColor;
	vec3 specular = 0.5f * pow(max(dot(V, R),0.0f),256) * LightColor;
	
	vec4  texA =  0.5f *  texture2D(DiffuseTexture, InterpolatedTexCoord);
	vec4  texB = 0.5f * texture2D(DiffuseTexture2, InterpolatedTexCoord);
	vec4 mixOne = mix(texA,texB, texA.a);
	
	vec3 phong = (ambient+diffuse+specular) *  mixOne;
	FragColor = vec4(phong, 1.0f);
}

//referencias de las funciones utilizadas
//http://www.shaderific.com/glsl-functions/


//referencias de mix
//http://distrustsimplicity.net/articles/texture-blending-in-glsl/
//http://www.shaderific.com/glsl-functions/
//https://www.khronos.org/opengl/wiki/Multitexture_with_GLSL
