#include"Model.hpp"


void Model::Draw(const Shader &shader){

    for(int i=0;i<meshes.size();i++){
        this->meshes[i].Draw(shader);
    }

}
void Model::Draw(const Shader &shader,int amount){
    for(int i=0;i<meshes.size();i++){
        this->meshes[i].Draw(shader,amount);
    }
}
void Model::loadModel(string path){

    Assimp::Importer importer;
    const aiScene*scene=importer.ReadFile(path,aiProcess_Triangulate|aiProcess_FlipUVs|aiProcess_CalcTangentSpace|aiProcess_GenSmoothNormals);
    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode){
        cout<<"MODEL LOADED ERROR..."<<importer.GetErrorString()<<endl;
        return;
    }
    directory=path.substr(0,path.find_last_of('\\'));
    processNode(scene->mRootNode,scene);
}
void Model::processNode(aiNode*node,const aiScene *scene){

    for(unsigned int i=0;i<node->mNumMeshes;i++){
        aiMesh*mesh=scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh,scene));
    }

    for(unsigned int i =0;i<node->mNumChildren;i++){
        processNode(node->mChildren[i],scene);
    }
    
}
Mesh Model::processMesh(aiMesh*mesh,const aiScene*scene){

    vector<Vertex>vertics;
    vector<GLuint>indics;
    vector<Texture>texutures;
    
    for(unsigned int i=0;i<mesh->mNumVertices;i++){
        Vertex vertex;
        vertex.Position=vec3(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);
        vertex.Normal=vec3(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);
        if(mesh->mTextureCoords[0]){
            vertex.Texcoords=vec2(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);

        }else{
            vertex.Texcoords=vec2(0.f,0.f);
        }
        vertics.push_back(vertex);
    }

    for(unsigned int i=0;i<mesh->mNumFaces;i++){
        aiFace face=mesh->mFaces[i];
        for(unsigned int j=0;j<face.mNumIndices;j++){
            indics.push_back(face.mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex>=0){
        aiMaterial *material=scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture>diffuseMaps=loadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
        texutures.insert(texutures.end(),diffuseMaps.begin(),diffuseMaps.end());
        vector<Texture>specularMaps=loadMaterialTextures(material,aiTextureType_SPECULAR,"texuture_specular");
        texutures.insert(texutures.end(),specularMaps.begin(),specularMaps.end());
        vector<Texture>normalMaps=loadMaterialTextures(material,aiTextureType_HEIGHT,"texture_normal");
        texutures.insert(texutures.end(),normalMaps.begin(),normalMaps.end());
        vector<Texture>heightMaps=loadMaterialTextures(material,aiTextureType_AMBIENT,"texture_height");
        texutures.insert(texutures.end(),heightMaps.begin(),heightMaps.end());
    }

    return Mesh(vertics,indics,texutures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial*mat,aiTextureType type,string typeName){
    
    vector<Texture>texutures;
    for(unsigned int i=0;i<mat->GetTextureCount(type);i++){
        aiString str;
        mat->GetTexture(type,i,&str);
        // str="D:\\LearnOpenGL\\Lesson_10_Assimp\\nanosuit\\"+string(str.C_Str());
        bool skip=false;
        for(unsigned int j=0;j<textures_loaded.size();j++){
            if(std::strcmp(str.C_Str(),textures_loaded[j].path.C_Str())==0){
                texutures.push_back(textures_loaded[j]);
                skip=true;
                break;
            }
        }
        if(!skip){
            Texture texture;
            texture.id=TextureFromFile(str.C_Str(),this->directory);
            texture.path=str.C_Str();
            texture.type=typeName;
            texutures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return texutures;

}
unsigned int Model::TextureFromFile(const char*path,const string&directory){

    string filename=string(path);
    filename=directory+"\\"+filename;
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    int width,height,nrChannels;
    unsigned char*data=stbi_load(filename.c_str(),&width,&height,&nrChannels,0);
    if(data){
        GLenum format;
        if(nrChannels==1){
            format=GL_RED;
        }
        if(nrChannels==3){
            format=GL_RGB;
        }
        if(nrChannels==4){
            format=GL_RGBA;
        }
        if(nrChannels==2){
            format=GL_R8;
        }
        // cout<<nrChannels<<endl;
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }else{
        cout<<"Texture load failed..."<<path<<" "<<filename<<endl;
        stbi_image_free(data);
    }
    
    return texture;

}
vec3 Model::Rayhit(vec3 postion,vec3 dir,mat4 Model){
    vec3 neareasthit=postion;
    for(int i=0;i<this->meshes.size();i++){
        // cout<<"enter"<<endl;
        vec3 hitpoint=hit(meshes[i].getBVHTree(),postion,dir,Model);
        if(hitpoint!=postion){
            if(neareasthit==postion||distance(neareasthit,postion),distance(hitpoint,postion)){
                neareasthit=hitpoint;
            }
        }
    }

   return neareasthit;
}
vec3 Model::hit(BVHNode*node,vec3 position,vec3 dir,mat4 Model){
    // cout<<"enter"<<endl;
    if(node->left==NULL&&node->right==NULL){
        // cout<<"enter"<<endl;
        vec3 neareastHit=position;
        vector<vec3>hitbox;
        hitbox.push_back(vec3(Model*vec4(node->Bounding_box[0],1.f)));
        hitbox.push_back(vec3(Model*vec4(node->Bounding_box[1],1.f)));
        if(!Utils::Box3dHit(position,dir,hitbox)){
            return neareastHit;
        }
        for(int i=0;i<node->objects.size();i++){
            vector<vec3>triangle;
            vec3 hitpoint;
            triangle.push_back(vec3(Model*vec4(node->objects[i].point1,1.f)));
            triangle.push_back(vec3(Model*vec4(node->objects[i].point2,1.f)));
            triangle.push_back(vec3(Model*vec4(node->objects[i].point3,1.f)));
            bool res=Utils::TriangleHit(position,dir,triangle,hitpoint);
            if(res){
                if(neareastHit==position||(distance(position,neareastHit)>distance(position,hitpoint))){
                    neareastHit=hitpoint;
                }
            }
        }
        return neareastHit;
    }
    vec3 lefthit=hit(node->left,position,dir,Model);
    vec3 righthit=hit(node->right,position,dir,Model);
    vec3 result=position;
    if(lefthit!=position)result=lefthit;
    if(righthit!=position){
        if(result==position||distance(result,position)>distance(righthit,position)){
            result=righthit;
        }
    }   
    return result;
}
void Model::initalMeshMatrics(mat4* modelMatrics,int amount){
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,amount*sizeof(mat4),modelMatrics,GL_STATIC_DRAW);
    for(int i=0;i<meshes.size();i++){
        meshes[i].initalMatrics();
    }
    glBindBuffer(GL_ARRAY_BUFFER,0);
}