#ifndef EARTH_H
#define EARTH_H
#include"Object.hpp"
#include"Moon.hpp"
class Earth:public Object{

    public:
    Moon* moon;
    Earth():Object(){
        Startup();
    }
    Earth(Model model,TransForm transform):Object(model,transform){
        Startup();
    }
    Earth(Model model,Moon* moon):Object(model){
        Startup();
        // TransForm transform;
        transform.Position=vec3(200.f,0.f,0.f);
        transform.Rotation=vec3(23.f,0.f,0.f);
        transform.Scale=vec3(1.f);
        ObjectName="Earth";
        this->moon=moon;
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
    string Name="Earth";

};



#endif