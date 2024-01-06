#ifndef SUN_H
#define SUN_H

#include "Object.hpp"
class Sun:public Object{

    public:
    Sun():Object(){
        Startup();
    }
    Sun(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Sun(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(0.f);
        transform.Rotation=vec3(90.f,0.f,0.f);
        transform.Scale=vec3(4.f);
        ObjectName="Sun";
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
    string Name="Sun";


};

#endif