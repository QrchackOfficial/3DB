#version 330 core

layout(location = 0) in vec3 vData;

void main() {
	// pass vertex data
	gl_Position.xyz = vData;
	gl_Position.w = 1.0;
}
