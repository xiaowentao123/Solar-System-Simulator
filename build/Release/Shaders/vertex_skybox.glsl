#version 330 core

layout(location=0) in vec3 aPos;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Texcoord;

void main(){

    vec4 finalPos=Projection*View*vec4(aPos,1.f);
    gl_Position=finalPos.xyww;

    Texcoord=aPos;


}