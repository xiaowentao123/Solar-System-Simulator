#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;
struct Material{

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

};

struct Material_tex{

    int diffuse;
    int specular;
    float shiniess;

};
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

struct Light_torch
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


class Shader
{
private:
    
    /* data */
public:
    unsigned int ID;
    Shader(const char* vertexPath,const char*fragmentPath);
    Shader();
    void use();
    void setBool(const string&name,bool value)const;
    void setInt(const string&name,int value)const;
    void setFloat(const string&name,float value)const;
    void setMat4(const string&name,mat4& matrix)const;
    void setVec3(const string&name,vec3&vector)const;
    void setMaterial(const vector<string>&names,Material&material)const;
    void setMaterial(const vector<string>&names,Material_tex&material)const;
    void setLight(const vector<string>&names,Light&light)const;
    void setLight(const vector<string>&names,Light_parallel&light)const;
    void setLight(const vector<string>&names,Light_torch&light)const;
    void setLights(const vector<vector<string>>&names,vector<Light>&lights)const;
    ~Shader();
};





#endif