
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
    vec3 ambient;               //����
    vec3 diffuse;               //������
    vec3 specular;              //����
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
    vec3 ambient = light.ambient * material.ambient;

    //���������
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - normal);
    vec3 diffUse = material.diffuse * light.diffuse;

    //���淴��
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    //�������ع��ɷ�ʽ����
    vec3 result = ambient + diffUse + specular;

    FragColor = vec4(result, 1.0f);
}
