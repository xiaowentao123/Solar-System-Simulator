#include"Rock.hpp"


void Rock::Startup(){
    
} 
void Rock::Tick(float deltaTime){
    if(isClickOn){
        glStencilFunc(GL_NOTEQUAL,12,0xFF);
        glStencilMask(0x00);
        // glDisable(GL_DEPTH_TEST);
        // glEnable(GL_DEPTH_TEST);

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
void Rock::Instance(Shader& shader,FpsCamera camera,mat4 projection){
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
void Rock::Instance(FpsCamera& camera,mat4 projection){
    glStencilFunc(GL_ALWAYS,12,0xFF);
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
void Rock::InstanceN(Shader& shader,FpsCamera camera,mat4 projection,int amount){
    shader.use();
    mat4 Model;
    shader.setMat4("Model",Model);
    shader.setMat4("View",camera.getLooAt());
    shader.setMat4("Projection",projection);
    
    this->lookCamera=camera;
    this->projection=projection;
    mesh.Draw(shader,amount);
}
vec3 Rock::Rayhit(vec3 dir){
    mat4 Model;
    Model=translate(Model,transform.Position);
    Model=scale(Model,transform.Scale*1.01f);
    return mesh.Rayhit(this->lookCamera.Postion,dir,Model);
}
