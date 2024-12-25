
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;


void main()
{
    //环境光照
    float ambientStrength = 0.1f;
    vec3 ambient = lightColor * ambientStrength;

    //漫反射光照
    vec3 normal = normalize(lightPos);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0, 0f);
    vec3 diffUse = diff * lightColor;

    vec3 result = (ambient * diffUse) * objectColor;

    FragColor = vec4(result, 1.0f);
}
