#ifndef MOON_H
#define MOON_H
#include"Object.hpp"
class Moon:public Object{

    public:
    Moon():Object(){
        Startup();
    }
    Moon(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Moon(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(230.f,0.f,0.f);
        transform.Rotation=vec3(0.f,0.f,0.f);
        transform.Scale=vec3(0.3f);
        ObjectName="Moon";
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
    string Name="Moon";




};
#endif