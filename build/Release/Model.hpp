#ifndef MODEL_H
#define MODEL_H

#include<vector>
#include"Mesh.hpp"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<string>
#include"stb_image.h"
#include"Utils.hpp"
using namespace Assimp;
#include<iostream>
class Model{

   public:
    Model(char*path){
        loadModel(path);
    }
    Model(){

    } 
    void Draw(const Shader &shader);
    void Draw(const Shader &shader,int amount);
    vec3 Rayhit(vec3 postion,vec3 dir,mat4 Model);
    void initalMeshMatrics(mat4* modelMatrics,int amount);
    private:
    vec3 hit(BVHNode*node,vec3 position,vec3 dir,mat4 Model);
    vector<Texture>textures_loaded;
    vector<Mesh>meshes;
    string directory;
    void loadModel(string path);
    void processNode(aiNode*node,const aiScene *scene);
    Mesh processMesh(aiMesh*mesh,const aiScene*scene);
    vector<Texture>loadMaterialTextures(aiMaterial*mat,aiTextureType type,string typeName);
    unsigned int TextureFromFile(const char*path,const string&directory);
    

};



#endif