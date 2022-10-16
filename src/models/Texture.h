#pragma once
#include <string>
#include <vector>

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

Texture loadTexture(char const* path);
Texture loadCubemap(const std::vector<std::string> &facesPaths);