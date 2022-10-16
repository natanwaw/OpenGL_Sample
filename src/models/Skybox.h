#pragma once

#include "Texture.h"
#include "Shader.h"

class Skybox
{
	unsigned VAO, VBO;
	Texture skyboxTexture;
public:
	Skybox(const std::vector<std::string> &faces);
	void Draw(Shader& shader);
};