#ifndef URANUS_H
#define URANUS_H
#include"Object.hpp"
class Uranus:public Object{

    public:
    Uranus():Object(){
        Startup();
    }
    Uranus(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Uranus(Model model):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(750.f,0.f,0.f);
        transform.Rotation=vec3(83.f,0.f,0.f);
        transform.Scale=vec3(5.f);
        ObjectName="Uranus";
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
    string Name="Uranus";




};


#endif