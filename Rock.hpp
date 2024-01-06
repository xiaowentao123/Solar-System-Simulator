#ifndef ROCK_H
#define ROCK_H

#include"Object.hpp"

class Rock:public Object{

    public:
    Rock():Object(){
        Startup();
    }
    Rock(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Rock(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(350.f,0.f,0.f);
        transform.Rotation=vec3(0.f,0.f,0.f);
        transform.Scale=vec3(1.f);
        ObjectName="Rock";
        // cout<<"inital"<<endl;
    }
    void Startup() override;
    void Tick(float deltaTime) override;
    void Instance(Shader& shader,FpsCamera camera,mat4 projection) override;
    void Instance(FpsCamera& camera,mat4 projection) override;
    void InstanceN(Shader& shader,FpsCamera camera,mat4 projection,int amount);
    vec3 Rayhit(vec3 dir) override;

    private:
    FpsCamera lookCamera;
    mat4 projection;

    public:
    string Name="Rock";





};
#endif