
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;


void main()
{
    //环境光照
    float ambientStrength = 0.1f;
    vec3 ambient = lightColor * ambientStrength;

    //漫反射光照
    vec3 normal = normalize(lightPos);
    vec3 lightDir = lightPos - FragPos;
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffUse = diff * lightColor;

    //镜面反射
    float specStrength = 0.5f;
    vec3 viewDir = viewPos - FragPos;   
    vec3 specDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, specDir), 0.0f), 32);
    vec3 specular = spec * specStrength * lightColor;

    //三个因素构成风式光照
    vec3 result = (ambient + diffUse + specular) * objectColor;

    FragColor = vec4(result, 1.0f);
}
