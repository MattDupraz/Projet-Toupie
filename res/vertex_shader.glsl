// VERTEX SHADER

attribute vec3 vertex;
attribute vec3 color;

uniform mat4 projection;
uniform mat4 translation;

varying vec3 result_color;

void main() {
	gl_Position = projection * translation * vec4(vertex, 1.0);
	result_color = color;
}
