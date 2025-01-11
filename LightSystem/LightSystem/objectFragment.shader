
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


struct Material
{
    sampler2D diffuse;               //漫反射  修改成贴图
    sampler2D specular;              //镜面    修改成贴图
    float shininess;            //光照强度
};

struct DirLight
{
    vec3 position;              //位置
    vec3 ambient;               //环境
    vec3 diffuse;               //漫反射
    vec3 specular;              //镜面
};


struct PointLight
{
    vec3 direction;             //位置

    vec3 ambient;               //环境
    vec3 diffuse;               //漫反射
    vec3 specular;              //镜面

    //用于计算衰减
    float constant;
    float linear;
    float quadratic;
};


uniform Material material;
uniform DirLight DirLight;
uniform PointLight DirLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewPos);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewPos,vec3 fragPos);

void main()
{
    //环境光照
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    //漫反射光照
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - normal);
    float diff = max(dot(lightDir, FragPos), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    //镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    //三个因素构成风式光照
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0f);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewPos)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    float diff = max(dot(normal, light.position), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    vec3 lightDir = light.position - FragPos;
    
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(lightDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    return ambient + diffuse + specular;
}
vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    float diff = max(dot(normal, light.position), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

    vec3 lightDir = light.position - FragPos;

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(lightDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    return ambient + diffuse + specular;
}


