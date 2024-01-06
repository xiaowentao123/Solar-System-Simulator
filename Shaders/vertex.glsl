#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexcoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 Normal;
out vec2 Texcoord;
out vec3 Pos;
void main(){

    gl_Position=Projection*View*Model*vec4(aPos,1.f);
    Normal=mat3(transpose(inverse(Model)))*aNormal;
    Texcoord=aTexcoord;
    Pos=vec3(Model*vec4(aPos,1.f));
}   