#ifndef MESH_H
#define MESH_H

#include<iostream>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include"Shader.hpp"
using namespace std;
using namespace glm;

struct Vertex{

    vec3 Position;
    vec3 Normal;
    vec2 Texcoords;

};
struct Texture{

    unsigned int id;
    string type;
    aiString path;

};
struct Pixel_Triangle{
    vec3 point1;
    vec3 point2;
    vec3 point3;
};
struct BVHNode{
    vector<vec3>Bounding_box;
    BVHNode*left,*right;
    vector<Pixel_Triangle>objects;
    BVHNode(vector<vec3>&Bounding_box,BVHNode*left,BVHNode*right,vector<Pixel_Triangle>&objects):
    Bounding_box(vector<vec3>(2,vec3(0.f))),
    left(NULL),right(NULL),objects(vector<Pixel_Triangle>()){

    }
    BVHNode():Bounding_box(vector<vec3>(2,vec3(0.f))),left(NULL),right(NULL){

    }
};
class Mesh
{
private:
    unsigned int VAO,VBO,EBO;
    BVHNode*root;
    void setupMesh();
    void initBVHTree(BVHNode*node,vector<Pixel_Triangle>&pixels,int nodeCapacity);
public:
    
    vector<Vertex>vertices;
    vector<GLuint>indics;
    vector<Texture>textures;
    vector<Pixel_Triangle>pixels;
    Mesh(vector<Vertex>vertices,vector<GLuint>indics,vector<Texture>textures);
    void Draw(const Shader& shader);
    void Draw(const Shader& shader,int amount);
    BVHNode* getBVHTree();
    void initalMatrics();
};


#endif