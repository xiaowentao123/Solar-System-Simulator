#ifndef OBJECT_H
#define OBJECT_H

#include<glad/glad.h>
#include"Model.hpp"
#include"Shader.hpp"
#include<iostream>
using namespace std;
using namespace glm;
struct TransForm{

    vec3 Position;
    vec3 Rotation;
    vec3 Scale;
};
class Object{

    public:
    TransForm transform;
    Model mesh;
    bool isClickOn=false;
    string ObjectName;
    Shader shader;
    float POV=45.f;
    Object(){
        Startup();
    }
    Object(Model model,TransForm transform):transform(transform),mesh(model){
        Startup();
    }
    Object(Model model){
        this->mesh=model;
    }
    Object(Model model,Shader&shader){
        this->mesh=model;
        this->shader=shader;
    }
    virtual void Tick(float deltaTime);
    virtual void Startup();
    virtual void Instance(Shader& shader,FpsCamera camera,mat4 projection);
    // virtual void Instance(FpsCamera camera,mat4 projection);
    virtual void Instance(FpsCamera& camera,mat4 projection);
    virtual vec3 Rayhit(vec3 dir){
        return vec3();
    }

};


#endif