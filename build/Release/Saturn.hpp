#ifndef SATURN_H
#define SATURN_H

#include"Object.hpp"
class Saturn:public Object{

    public:
    Saturn():Object(){
        Startup();
    }
    Saturn(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Saturn(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(650.f,0.f,0.f);
        transform.Rotation=vec3(26.f,0.f,0.f);
        transform.Scale=vec3(0.05f);
        ObjectName="Saturn";
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
    string Name="Saturn";



};
#endif