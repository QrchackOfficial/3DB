#version 330 core

in vec2 UV;

out vec3 oColor;

uniform sampler2D inTexture;

void main() {
	// Forward buffered data
	oColor = texture(inTexture, UV).rgb;
}
