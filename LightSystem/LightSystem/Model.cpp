#include "Model.h"
#include "../../OpenGL/OpenGL/stb_image.h"

using std::string;
Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && !scene->mRootNode)
		return;

	strDirectory = path.substr(0, path.find_last_of("/"));

	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* pMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(pMesh, scene));
	}
	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertex;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex temp;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		temp.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		temp.normal = vector;

		if (mesh->mTextureCoords[i])
		{
			temp.texCoords.x = mesh->mTextureCoords[0][i].x;
			temp.texCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			temp.texCoords.x = 0.2f;
			temp.texCoords.y = 0.2f;
		}
		
		vertex.push_back(temp);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> texDiffuse = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), texDiffuse.begin(), texDiffuse.end());
		std::vector<Texture> texSpecular = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_specular");
		textures.insert(textures.end(), texSpecular.begin(), texSpecular.end());
	}

	return Mesh(vertex,indices,textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), strDirectory);
		texture.path = strDirectory;
		texture.type = typeName;
		textures.push_back(texture);
	}

	return textures;
}

void Model::draw(Shader& shader)
{
	for (int i = 0; i < meshes.size(); ++i)
		meshes[i].draw(shader);
}

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
{
	unsigned int nTexture;
	glGenTextures(1, &nTexture);

	int iWidth, iHeight, iChannel;
	unsigned char* spData = stbi_load(path, &iWidth, &iHeight, &iChannel, 0);
	if (spData)
	{
		GLenum enFormat = GL_RED;
		if (iChannel == 0) enFormat = GL_RED;
		if (iChannel == 3) enFormat = GL_RGB;
		if (iChannel == 4) enFormat = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, nTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, (int)enFormat, iWidth, iHeight, 0, enFormat, GL_UNSIGNED_BYTE, spData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	stbi_image_free(spData);
	return nTexture;
}
