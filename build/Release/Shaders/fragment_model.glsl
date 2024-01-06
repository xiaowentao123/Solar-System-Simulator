#version 330 core

out vec4 FragColor;

uniform sampler2D texture_diffuse1;


in vec3 Pos;
in vec3 Normal;
in vec2 Texcoord;


void main(){

    FragColor=texture(texture_diffuse1,Texcoord);

}