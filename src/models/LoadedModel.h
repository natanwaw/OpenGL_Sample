#pragma once
#include <assimp/scene.h>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Model.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class LoadedModel : public Model
{
public:
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	LoadedModel(char* path) {
		loadModel(path);
	}

protected:
	virtual void DrawShape(Shader& shader) override;

private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};