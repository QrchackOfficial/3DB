#version 330 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iColor;
out vec3 vColor;

uniform mat4 MVP;

void main() {
	// Transform vertex data
	gl_Position = MVP * vec4(iPosition, 1);

	// Forward color data to the fragment shader
	vColor = iColor;
}
