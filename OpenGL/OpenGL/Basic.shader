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

uniform vec4 u_Color;
 
void main(void)
{
	color = u_Color;    //rgba
};