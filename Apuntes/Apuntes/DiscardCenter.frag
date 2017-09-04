#version 330

in vec3 InterpolatedColor;
in vec4 gl_FragCoord;

out vec4 FragColor;

void main()
{
	vec2 pixelPositionInWindow = gl_FragCoord.xy;
	if(((pixelPositionInWindow.x/400)* 2.0 - 1.0 > -0.5 && (pixelPositionInWindow.x/400)* 2.0 - 1.0 < 0.5 ) && ((pixelPositionInWindow.y/400)* 2.0 - 1.0 > -0.5 && (pixelPositionInWindow.y/400)* 2.0 - 1.0 < 0.5 ))
	discard;

	FragColor = vec4(InterpolatedColor, 1.0f);
}