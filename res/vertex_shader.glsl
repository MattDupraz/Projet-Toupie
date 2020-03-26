// VERTEX SHADER

attribute vec3 aVertex;
attribute vec3 aColor;
attribute vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec3 color;
varying vec3 normal;
varying vec3 pos;

void main() {
	gl_Position = projection * view * model * vec4(aVertex, 1.0);
	color = aColor;
	normal = vec3(model * vec4(aNormal, 1.0));
	pos = vec3(model * vec4(aVertex, 1.0));
}
