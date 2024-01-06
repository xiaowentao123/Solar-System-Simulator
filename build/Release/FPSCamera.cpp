#include "FPSCamera.hpp"


FpsCamera::FpsCamera(vec3 position,vec3 front,vec3 up,float sensitivity,float speed,float yaw,float pitch){

    this->Postion=position;
    this->Front=front;
    this->Up=up;
    this->sensitivity=sensitivity;
    this->speed=speed;
    this->yaw=yaw;
    this->pitch=pitch;

}
mat4 FpsCamera::getLooAt(){
    mat4 result;
    result=lookAt(this->Postion,this->Postion+this->Front,this->Up);
    return result;
}
void FpsCamera::processKeyboradInput(float deltatime,DIRECTION direction){
    float movespeed=this->speed*deltatime;
    if(direction==FORWARD){
        this->Postion+=movespeed*normalize(vec3(this->Front.x,0.f,this->Front.z));
    }
    if(direction==BACK){
        this->Postion-=movespeed*normalize(vec3(this->Front.x,0.f,this->Front.z));
    
    }
    if(direction==LEFT){
        this->Postion+=movespeed*normalize(cross(this->Up,this->Front));
    }
    if(direction==RIGHT){
        this->Postion-=movespeed*normalize(cross(this->Up,this->Front));
    }
    if(direction==UP){
        this->Postion+=movespeed*normalize(WORDUP);
    }
    if(direction==DOWN){
        this->Postion-=movespeed*normalize(WORDUP);
    }
}
void FpsCamera::processMouseInput(float xoffset,float yoffset){
    // xoffset=glm::clamp(xoffset,-1.f,1.f);
    // yoffset=glm::clamp(yoffset,-1.f,1.f);
    xoffset*=this->sensitivity;
    yoffset*=this->sensitivity;
    this->pitch+=yoffset;
    this->yaw+=xoffset;

    if(this->pitch>89.f)this->pitch=89.f;
    if(this->pitch<-89.f)this->pitch=-89.f;

    this->Front.x=cos(radians(this->pitch))*cos(radians(this->yaw));
    this->Front.y=sin(radians(this->pitch));
    this->Front.z=cos(radians(this->pitch))*sin(radians(this->yaw));
}
void FpsCamera::Tick(float deltatime){
    if(isMove){
        
        if(distance(Postion,moveTarget+vec3(0.f,0.f,1.f))<0.01f&&distance(Front,normalize(moveTarget-Postion))<0.001f){
            isMove=false;
            // isFollow=true;
            isLock=false;
            this->Postion=moveTarget+vec3(0.f,0.f,1.f);
            this->Front=normalize(moveTarget-Postion);
            float oriyawAngle,oripitchAngle;
            float cosyawAngle=dot(normalize(vec3(Front.x,0,Front.z)),vec3(1.f,0.f,0.f));
            float cospitchAngle=dot(normalize(Front),normalize(vec3(Front.x,0.f,Front.z)));
            if(Front.z>=0.f){
                // cout<<">0"<<endl;
                oripitchAngle=-degrees(acos(cospitchAngle));
            }else{
                // cout<<"<0"<<endl;
                oripitchAngle=degrees(acos(cospitchAngle));
            }
            oriyawAngle=degrees(glm::acos(cosyawAngle));
            this->yaw=-90.f;
            this->pitch=0.f;
        }
        Front=mix(Front,normalize(moveTarget-Postion),0.1f);
        Postion=mix(Postion,moveTarget+vec3(0.f,0.f,1.f),0.1f);
        
        // cout<<"move!"<<endl;
    }
}