#pragma once

#include <vector>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);

	unsigned int getVAO() const {
		return this->VAO;
	}

	unsigned int getVBO() const {
		return this->VBO;
	}

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};