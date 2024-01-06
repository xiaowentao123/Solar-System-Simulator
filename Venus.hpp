#ifndef VENUS_H
#define VENUS_H

#include"Object.hpp"
class Venus:public Object{

    public:
    Venus():Object(){
        Startup();
    }
    Venus(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Venus(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(150.f,0.f,0.f);
        transform.Rotation=vec3(0.f);
        transform.Scale=vec3(3.3f);
        ObjectName="Venus";
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
    string Name="Venus";

};

#endif  