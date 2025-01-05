
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
    sampler2D diffuse;               //������  �޸ĳ���ͼ
    sampler2D specular;              //����    �޸ĳ���ͼ
    float shininess;            //����ǿ��
};

struct Light
{
    vec3 position;              //λ��
    vec3 ambient;               //����
    vec3 diffuse;               //������
    vec3 specular;              //����
};

uniform Material material;
uniform Light light;

void main()
{
    //��������
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

    //���������
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - normal);
    float diff = max(dot(lightDir, FragPos), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));

    //���淴��
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    //�������ع��ɷ�ʽ����
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0f);
}
