#version 330 core

layout(location = 0) in vec3 aPos;      // 假设这是顶点位置的attribute变量
layout(location = 1) in vec3 aNormal;   // 法向量
layout(location = 2) in vec2 aTexCoords;   // 材质坐标

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec2 texCoords;

void main()
{
    texCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0); // 设置gl_Position内建变量
}