#version 330 core

layout(location = 0) in vec3 aPos;      // 假设这是顶点位置的attribute变量
layout(location = 1) in vec3 aNormal;   // 法向量

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // 设置gl_Position内建变量
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = aNormal;
}
