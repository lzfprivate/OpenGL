
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 texCoords;


struct Material
{
    sampler2D diffuse;               //漫反射  修改成贴图
    sampler2D specular;              //镜面    修改成贴图
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
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

    //漫反射光照
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - normal);
    float diff = max(dot(lightDir, FragPos), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    //三个因素构成风式光照
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0f);
}
