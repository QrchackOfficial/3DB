#version 330 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iTexture;

out vec2 UV;

uniform mat4 MVP;

void main() {
	
	// Transform vertex data
	gl_Position = MVP * vec4(iPosition, 1);

	// Forward texture to the fragment shader
	UV = iTexture;
}
