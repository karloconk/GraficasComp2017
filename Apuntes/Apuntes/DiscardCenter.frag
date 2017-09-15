#version 330

in vec3 InterpolatedColor;
in vec4 gl_FragCoord;

out vec4 FragColor;

//esto es la resolucion de pantalla en pixeles
uniform vec2 Resolution;

void main()
{

	//posisicion de pizel en pantalla [(0,0)- (1,1)]
	vec2 p = gl_FragCoord.xy /Resolution;
	//calculando un v ec que va al pixel del centro
	vec2 q = p - vec2(0.5f,0.5f);
	//pretty self-explanatory
	if(length(q) < 0.25f)
	discard;

	FragColor = vec4(InterpolatedColor, 1.0f);
}

