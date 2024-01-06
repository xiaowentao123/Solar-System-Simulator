#version 330 core

struct Light{

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

};
struct Light_parallel{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;
uniform sampler2D texture_diffuse5;
uniform sampler2D texture_diffuse6;

uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform sampler2D texture_specular4;
uniform sampler2D texture_specular5;
uniform sampler2D texture_specular6;

uniform vec3 ViewPos;
uniform Light light;
uniform Light_parallel light_parallel;

in vec3 Normal;
in vec2 Texcoord;
in vec3 Pos;

out vec4 FragColor;

void main(){
    float dis=length(light.position-Pos);
    float k=1.0/(dis*dis*light.quadratic+dis*light.linear+light.constant);
    vec3 result=vec3(0.f);
    vec3 ambientLight=light.ambient*vec3(texture(texture_diffuse1,Texcoord));
    result+=ambientLight;
    // vec3 lightDir=normalize(light.position-Pos);
    vec3 lightDir=normalize(light.position-Pos);
    vec3 norm=normalize(Normal);
    float diff=max(dot(lightDir,norm),0.f);
    vec3 diffuseLight=light.diffuse*diff*vec3(texture(texture_diffuse1,Texcoord));
    result+=diffuseLight;
    vec3 viewDir=normalize(ViewPos-Pos);
    vec3 reflectDir=normalize(reflect(-lightDir,norm));
    vec3 halfDir=normalize(lightDir+viewDir);
    float specular=pow(max(dot(halfDir,norm),0.f),4.f);
    vec3 specularLight=light.specular*specular*vec3(0.5f,0.5f,0.5f);
    result+=specularLight;
    // result*=k;
    FragColor=vec4(result,1.f);
}