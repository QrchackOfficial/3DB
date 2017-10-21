#include <vector>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec2.hpp>
#include <iostream>

using glm::vec3;
using glm::vec2;
using std::vector;

/* TODO Add support for:
 * o binary files
 * o animations, bones
 * o multiple UVs
 * o attributes should be optional
 * o move to proper C++ code
 * o loading from string array
 */

/**
 * \brief
 * \param path
 * \param outVertices
 * \param outUVs
 * \param outNormals
 * \return false on error
 */
bool loadOBJ(const char* path,
			 std::vector<vec3>& outVertices,
			 std::vector<vec2>& outUVs,
			 std::vector<vec3>& outNormals
) {
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<vec3> vVertices;
	vector<vec2> vUVs;
	vector<vec3> vNormals;

	// Load the file
	FILE* file = fopen(path, "r");
	if (!file) {
		std::cout << "Image " << path << " could not be opened :(\n";
		return false;
	}
	while (true) {
		// Assume max 128 characters
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			// EOF reached
			break;

		// Load vertices
		if (strcmp(lineHeader, "v") == 0) {
			// Create a vec3 and load data
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			// Add to temp_vertices array
			vVertices.push_back(vertex);
		}
		// Load UVs
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			vUVs.push_back(uv);
		}
		// Load normals
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			vNormals.push_back(normal);
		}
		// Load faces
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
								 &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				std::cout << "Error parsing OBJ file: " << path << ". Unknown format" << std::endl;
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	// Parse data into OpenGL
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		vec3 vertex = vVertices[vertexIndex - 1];
		outVertices.push_back(vertex);
	}
}