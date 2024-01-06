#ifndef MERCURY_H
#define MERCURY_H

#include"Object.hpp"

class Mercury:public Object{

    public:
    Mercury():Object(){
        Startup();
    }
    Mercury(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Mercury(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(100.f,0.f,0.f);
        transform.Rotation=vec3(0.f);
        transform.Scale=vec3(1.f);
        ObjectName="Mercury";
        // cout<<"inital"<<endl;
    }
    void Startup() override;
    void Tick(float deltaTime) override;
    void Instance(Shader& shader,FpsCamera camera,mat4 projection) override;
    void Instance(FpsCamera& camera,mat4 projection) override;
    vec3 Rayhit(vec3 dir) override;

    private:
    FpsCamera* lookCamera;
    mat4 projection;

    public:
    string Name="Mercury";

};


#endif