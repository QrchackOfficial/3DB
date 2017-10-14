#include <cstdio>
#include <iostream>
#include <GL/glew.h>

GLuint loadBMP(const char* imgPath) {
	std::cout << "Loading image " << imgPath << std::endl;
	FILE* f = fopen(imgPath, "rb");
	if (!f) {
		std::cout << "Image " << imgPath << " could not be opened :(\n";
		return 0;
	}

	// Header check
	unsigned char header[54];
	if (fread(header, 1, 54, f) != 54) {
		std::cout << imgPath << " is not a valid BMP file\n";
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		std::cout << imgPath << " is not a valid BMP file\n";
	}

	GLuint dataPos = *(int*)&header[0x0a];
	GLuint imgSize = *(int*)&header[0x22];
	GLuint width = *(int*)&header[0x12];
	GLuint height = *(int*)&header[0x16];

	if (imgSize == 0)
		imgSize = width * height * 3; // 3 -> RGB
	if (dataPos == 0)
		dataPos = 54; // header size

	auto rawData = new unsigned char[imgSize];
	fread(rawData, 1, imgSize, f);
	fclose(f);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, rawData);
	delete[] rawData;

	// Poor filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Nice trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate required mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}
