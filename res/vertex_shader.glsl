// VERTEX SHADER

attribute vec3 aPos;
attribute vec3 aColor;
attribute vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 translation;
uniform mat4 model;

varying vec3 pos;
varying vec3 color;
varying vec3 normal;

void main() {
	gl_Position = projection * view * translation * model * vec4(aPos, 1.0);
	color = aColor;
	normal = normalize(vec3(model * vec4(aNormal, 1.0)));
	pos = vec3(translation * model * vec4(aPos, 1.0));
}
