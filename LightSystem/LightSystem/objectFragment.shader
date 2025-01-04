
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;


struct Material
{
    vec3 ambient;               //环境
    vec3 diffuse;               //漫反射
    vec3 specular;              //镜面
    float shininess;            //光照强度
};

struct Light
{
    vec3 position;              //位置
    vec3 ambient;               //环境
    vec3 diffuse;               //漫反射
    vec3 specular;              //镜面
};

uniform Material material;
uniform Light light;

void main()
{
    //环境光照
    vec3 ambient = light.ambient * material.ambient;

    //漫反射光照
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - normal);
    vec3 diffUse = material.diffuse * light.diffuse;

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    //三个因素构成风式光照
    vec3 result = ambient + diffUse + specular;

    FragColor = vec4(result, 1.0f);
}
