// FRAGMENT SHADER

varying vec3 color;
varying vec3 normal;
varying vec3 pos;

uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;
	vec3 lightVec = normalize(lightPos - pos);
	float diffusionStrength = max(dot(normal, lightVec), 0.0);
	vec3 diffusion = diffusionStrength * lightColor;
	
	gl_FragColor = vec4((ambient + diffusion) * color, 1.0);
}
