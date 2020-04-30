// VERTEX SHADER

attribute vec3 aPos;
attribute vec3 aColor;
attribute vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 translation;
uniform mat4 orientation;
uniform mat4 scale;

varying vec3 pos;
varying vec3 color;
varying vec3 normal;

void main() {
	gl_Position = projection * view * translation * orientation * scale * vec4(aPos, 1.0);
	color = aColor;
	normal = normalize(vec3(orientation * scale * vec4(aNormal, 1.0)));
	pos = vec3(translation * orientation * scale * vec4(aPos, 1.0));
}
