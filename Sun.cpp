#include "Sun.hpp"


void Sun::Startup(){

}

void Sun::Tick(float deltaTime){
    if(isClickOn){
        glStencilFunc(GL_NOTEQUAL,3,0xFF);
        glStencilMask(0x00);
        // glDisable(GL_DEPTH_TEST);

        Shader container("Shaders/vertex.glsl","Shaders/container.glsl");
        container.use();
        mat4 Model;
        Model=translate(Model,transform.Position);
        Model=rotate(Model,radians(transform.Rotation.z),vec3(0.f,0.f,1.f));
        Model=rotate(Model,radians(transform.Rotation.y),vec3(0.f,1.f,0.f));
        Model=rotate(Model,radians(transform.Rotation.x),vec3(1.f,0.f,0.f));
        Model=scale(Model,transform.Scale*vec3(1.02f));

        container.setMat4("Model",Model);
        container.setMat4("View",this->lookCamera.getLooAt());
        container.setMat4("Projection",this->projection);

        mesh.Draw(container);

        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
        glStencilFunc(GL_ALWAYS,1,0xFF);
    }
}

void Sun::Instance(Shader& shader,FpsCamera camera,mat4 projection) {
    glStencilFunc(GL_ALWAYS,3,0xFF);
    shader.use();
    mat4 Model;
    Model=translate(Model,transform.Position);
    Model=rotate(Model,radians(transform.Rotation.z),vec3(0.f,0.f,1.f));
    Model=rotate(Model,radians(transform.Rotation.y),vec3(0.f,1.f,0.f));
    Model=rotate(Model,radians(transform.Rotation.x),vec3(1.f,0.f,0.f));
    Model=scale(Model,transform.Scale);
    shader.setMat4("Model",Model);
    shader.setMat4("View",camera.getLooAt());
    shader.setMat4("Projection",projection);
    shader.setVec3("ViewPos",camera.Postion);
    this->lookCamera=camera;
    this->projection=projection;
    mesh.Draw(shader);
    glStencilFunc(GL_ALWAYS,1,0xFF);
}

vec3 Sun::Rayhit(vec3 dir) {
    mat4 Model;
    Model=translate(Model,transform.Position);
    Model=scale(Model,transform.Scale*vec3(1.01f));
    return mesh.Rayhit(this->lookCamera.Postion,dir,Model);
}

void Sun::Instance(FpsCamera& camera,mat4 projection){
    // cout<<"earth instance"<<endl;
    shader.use();
    mat4 Model;
    Model=translate(Model,transform.Position);
    Model=rotate(Model,radians(transform.Rotation.z),vec3(0.f,0.f,1.f));
    Model=rotate(Model,radians(transform.Rotation.y),vec3(0.f,1.f,0.f));
    Model=rotate(Model,radians(transform.Rotation.x),vec3(1.f,0.f,0.f));
    Model=scale(Model,transform.Scale);
    shader.setMat4("Model",Model);
    shader.setMat4("View",camera.getLooAt());
    shader.setMat4("Projection",projection);
    shader.setVec3("ViewPos",camera.Postion);
    this->lookCamera=camera;
    this->projection=projection;
    mesh.Draw(shader);
}