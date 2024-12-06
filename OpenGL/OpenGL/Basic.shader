#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
 
void main(void)
{
gl_Position = position;
};
// 指定片段着色器
#shader fragment
#version 330 core
 
layout(location = 0) out vec4 color;
 
void main(void)
{
color = vec4(1.0 , 0.8 , 0.3 , 1.0);    //rgba
};