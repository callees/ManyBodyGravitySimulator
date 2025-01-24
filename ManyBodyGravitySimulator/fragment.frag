#version 330 core
out vec4 FragColor;
 
uniform vec2 iResolution;
uniform float normalisedMass;
void main()
{ 
	vec2 pos = (2.0*gl_PointCoord) -1.0;

	float distance = dot(pos, pos);
	if(distance > 1.0) discard;
	
//	FragColor.rgb = vec3(normalisedMass,0.1-distance, 1-distance);
	FragColor.rgb = vec3(1.0,1.0, 1.0);
}