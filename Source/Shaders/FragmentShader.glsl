#version 330 core

in vec3 vColor;
out vec3 oColor;

void main() {
	// Forward buffered data
	oColor = vColor;
}
