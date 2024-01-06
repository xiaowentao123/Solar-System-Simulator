#include"SkyBox.hpp"



void SkyBox::setupMesh(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD,Mesh init Failed..."<<endl;
        return ;
    }
    unsigned int VAO,VBO,texuture_cube;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    texuture_cube=Utils::loadCubemap(this->faces);
    if(texuture_cube==-1){
        cout<<"Cubemap load failed..."<<endl;
    }
    
    this->VAO=VAO;
    this->VBO=VBO;
    this->texuture_cube=texuture_cube;

}
void SkyBox::DrawBox(Shader &shader){


    glBindVertexArray(this->VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP,this->texuture_cube);
    glDrawArrays(GL_TRIANGLES,0,36);

    
}