#ifndef MARS_H
#define MARS_H

#include"Object.hpp"

class Mars:public Object{

    public:
    Mars():Object(){
        Startup();
    }
    Mars(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Mars(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(300.f,0.f,0.f);
        transform.Rotation=vec3(25.f,0.f,0.f);
        transform.Scale=vec3(0.5f);
        ObjectName="Mars";
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
    string Name="Mars";



};

#endif