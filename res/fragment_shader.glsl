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
	float lightIntensity = min(1.0, 1000.0/dot(lightPos - pos, lightPos - pos));
	float diffusionStrength = lightIntensity * (1.0 - ambientStrength) * max(dot(normal, lightVec), 0.0);
	vec3 diffusion = diffusionStrength * lightColor;
	// diffusion2 would be the light that reflected from the floor
	float floorDiffusionStrength = lightIntensity * 0.6;
	float diffusion2Strength = (1.0 - ambientStrength - diffusionStrength) *
		floorDiffusionStrength * max(dot(normal, vec3(lightVec.x, -lightVec.y, lightVec.z)), 0.0);
	vec3 diffusion2 = diffusion2Strength * lightColor;
	
	gl_FragColor = vec4((ambient + diffusion + diffusion2) * color, 1.0);
}
