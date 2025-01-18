#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertex, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_nVAO(0),m_nVBO(0),m_nEBO(0)
{
    
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &m_nVAO);
    glGenBuffers(1, &m_nVBO);
    glGenBuffers(1, &m_nEBO);

    glBindVertexArray(m_nVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_nVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // 顶点法线
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    // 顶点纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(3);

    // vertex bitangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    // ids
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
    glEnableVertexAttribArray(5);

    // weights
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_weights));
    glEnableVertexAttribArray(6);
    
    glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
    unsigned long iDiffuseNr = 1, iSpecularNr = 1,iNormalNr = 1,iHeightNr = 1;
    for (size_t i = 0; i < textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string strNumber = "";
        if (textures[i].type == "texture_diffuse")
        {
            strNumber = std::to_string(iDiffuseNr++);
        }
        else if (textures[i].type == "texture_specular")
        {
            strNumber = std::to_string(iSpecularNr++);
        }
        else if (textures[i].type == "texture_height")
        {
            strNumber = std::to_string(iNormalNr++);
        }
        else if (textures[i].type == "texture_normal")
        {
            strNumber = std::to_string(iHeightNr++);
        }
        shader.setValue1i(("material." + textures[i].type + strNumber).c_str(), i);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_nVAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}
