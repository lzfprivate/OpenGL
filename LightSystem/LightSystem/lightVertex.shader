#version 330 core
out vec4 FragColor;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // ����gl_Position�ڽ�����
}