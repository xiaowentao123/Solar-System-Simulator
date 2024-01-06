#ifndef NEPTUNE_H
#define NEPTUNE_H

#include"Object.hpp"
class Neptune:public Object{

    public:
    Neptune():Object(){
        Startup();
    }
    Neptune(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Neptune(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(850.f,0.f,0.f);
        transform.Rotation=vec3(28.f,0.f,0.f);
        transform.Scale=vec3(5.f);
        ObjectName="Neptune";
        // cout<<"inital"<<endl;
    }
    void Startup() override;
    void Tick(float deltaTime) override;
    void Instance(Shader& shader,FpsCamera camera,mat4 projection) override;
    void Instance(FpsCamera& camera,mat4 projection) override;
    vec3 Rayhit(vec3 dir) override;

    private:
    FpsCamera lookCamera;
    mat4 projection;

    public:
    string Name="Neptune";




};
#endif