#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexcoord;
layout(location=3) in mat4 instanceMatrix;


uniform mat4 View;
uniform mat4 Projection;

out vec3 Normal;
out vec2 Texcoord;
out vec3 Pos;



void main(){


    gl_Position=Projection*View*instanceMatrix*vec4(aPos,1.f);
    Texcoord=aTexcoord;
    Normal=mat3(transpose(inverse(instanceMatrix)))*aNormal;
    Pos=vec3(instanceMatrix*vec4(aPos,1.f));
}