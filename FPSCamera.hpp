#ifndef FPSCAMERA_H
#define FPSCAMERA_H
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;
const vec3 WORDPOINT=vec3(0.f,0.f,0.f);
const float SENSITIVITY=0.05f;
const float SPEED=10.f;
const vec3 WORDUP=vec3(0.f,1.f,0.f);
enum DIRECTION{
    FORWARD,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN

};
class FpsCamera{
    public:
    vec3 Postion;
    vec3 Front;
    vec3 Up;
    vec3 moveTarget;
    float sensitivity;
    float speed;
    float yaw;
    float pitch;
    bool isMove=false;
    bool isLock=false;
    bool isFollow=false;
    FpsCamera(vec3 position=WORDPOINT,vec3 front=vec3(0.f,0.f,-1.f),vec3 up=WORDUP,float sensitivity=SENSITIVITY,float speed=SPEED,float yaw=-90.f,float pitch=0.f);
    // FpsCamera();
    mat4 getLooAt();
    // mat4 getProjection();
    void processKeyboradInput(float deltatime,DIRECTION direction);
    void processMouseInput(float xoffset,float yoffset);
    void Tick(float deltatime);
    private:
    


};

#endif