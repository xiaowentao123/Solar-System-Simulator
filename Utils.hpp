#ifndef UTILS_H
#define UTILS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"FPSCamera.hpp"
#include"stb_image.h"
using namespace std;
using namespace glm;
class Utils{

    public:

    static bool Box3dHit(vec3 ori,vec3 dir,vector<vec3>box);
    static bool TriangleHit(vec3 ori,vec3 dir,vector<vec3>&triangle,vec3&hitpoint);
    static vec3 getRay(float x,float y,int screenWidth,int screenHeight,mat4 projection,FpsCamera camera);
    static unsigned int loadCubemap(vector<string>&faces);
    static mat4* loadMatrices(int amount,float radius,float offset);
};

#endif