#version 330 core

layout(location = 0) in vec3 aPos;      // �������Ƕ���λ�õ�attribute����
layout(location = 1) in vec3 aNormal;   // ������

out vec3 Normal;
out vec3 FragPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = aNormal;
    gl_Position = projection * view * model * vec4(FragPos, 1.0); // ����gl_Position�ڽ�����
}