#pragma once
#include <glm/detail/type_vec3.hpp>
#include <vector>

bool loadOBJ(const char* path,
			 std::vector<glm::vec3>& outVertices,
			 std::vector<glm::vec2>& outUVs,
			 std::vector<glm::vec3>& outNormals
);
