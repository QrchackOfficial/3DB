#version 330 core

layout(location = 0) in vec3 vData;

uniform mat4 MVP;

void main() {
	// Transform vertex data
	gl_Position = MVP * vec4(vData, 1);
}
