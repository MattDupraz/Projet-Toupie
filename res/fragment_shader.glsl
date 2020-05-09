// FRAGMENT SHADER

varying vec3 color;
varying vec3 normal;
varying vec3 pos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - pos);
	float dist = length(lightPos - pos);

	float ambient = 0.2;
	float lightBrightness = 20.0;

	float lightIntensity = lightBrightness/dist;
	float diffusion = lightIntensity * max(dot(norm, lightDir), 0.0);

	float floorReflectivity = 0.4;
	vec3 reflectedLightPos = vec3(lightPos.x, -lightPos.y, lightPos.z);
	vec3 reflectedLightDir = normalize(reflectedLightPos - pos);
	float reflectedDist = length(reflectedLightPos - pos);
	float reflectedLightIntensity = floorReflectivity * lightBrightness/reflectedDist;
	float reflectedDiffusion = reflectedLightIntensity * max(dot(norm,
				reflectedLightDir), 0.0);

	float objectReflectivity = 0.5;
	float shininess = 16.0;
	vec3 viewDir = normalize(viewPos - pos);
	float viewDist = length(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specularLightIntensity = objectReflectivity *
		lightBrightness/reflectedDist;
	float specular = specularLightIntensity * pow(max(dot(viewDir, reflectDir),
				0.0), shininess);
	
	vec3 resultLight = (ambient + diffusion + reflectedDiffusion + specular) * lightColor;

	gl_FragColor = vec4(resultLight * color, 1.0);
}
