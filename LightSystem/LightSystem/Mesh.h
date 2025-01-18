#pragma once

#include <glad.h>
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include "Shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
    glm::vec3 position;         //位置
    glm::vec3 normal;           //法线位置
    glm::vec2 texCoords;        //材质坐标

    glm::vec3 tangent;
    glm::vec3 bitangent;
    
    int       m_BoneIDs[MAX_BONE_INFLUENCE];
    float     m_weights[MAX_BONE_INFLUENCE];        //权重

};

    
struct Texture
{
    unsigned int id;            //id
    std::string type;           //类型
    std::string path;           //路径
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertex, std::vector<unsigned int> indices, std::vector<Texture> textures);

public:
    std::vector<Vertex>  vertex;
    std::vector<unsigned int> indices;
    std::vector<Texture>  textures;

private:
    unsigned int m_nVAO, m_nVBO, m_nEBO;

private:
    void setupMesh();

public:
    void draw(Shader& shader);

};




