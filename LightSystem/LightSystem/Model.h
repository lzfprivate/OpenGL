#pragma once
#include <vector>
#include <Assimp/include/Importer.hpp>
#include <Assimp/include/scene.h>
#include <Assimp/include/postprocess.h>
#include "Mesh.h"


unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(const std::string& path);


private:
	std::vector<Mesh> meshes;				//场景网格
	std::string strDirectory;				//文件路径

private:
	void loadModel(const std::string& path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

public:
	void draw(Shader& shader);
};

