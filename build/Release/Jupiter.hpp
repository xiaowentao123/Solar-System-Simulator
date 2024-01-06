#ifndef JUPITER_H
#define JUPITER_H

#include"Object.hpp"

class Jupiter:public Object{

    public:
    Jupiter():Object(){
        Startup();
    }
    Jupiter(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Jupiter(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(550.f,0.f,0.f);
        transform.Rotation=vec3(0.f,0.f,0.f);
        transform.Scale=vec3(10.f);
        ObjectName="Jupiter";
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
    string Name="Jupiter";

};

#endif