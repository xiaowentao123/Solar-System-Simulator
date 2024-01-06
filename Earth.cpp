#include"Earth.hpp"

void Earth::Tick(float deltaTime){

    if(isClickOn){
        glStencilFunc(GL_NOTEQUAL,2,0xFF);
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
    if(!isClickOn){
        this->transform.Position.x=200*glm::cos(radians(glfwGetTime()*3));
        this->transform.Position.z=200*glm::sin(radians(glfwGetTime()*3));
    }
    if(!moon->isClickOn){
        moon->transform.Position.x=this->transform.Position.x+30*glm::cos(radians(glfwGetTime()*36));
        moon->transform.Position.z=this->transform.Position.z+30*glm::sin(radians(glfwGetTime()*36));
    }
}

void Earth::Instance(Shader &shader,FpsCamera camera,mat4 projection)
{   

    // Shader shader("Shaders/vertex.glsl","Shaders/earth.glsl");
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
  
    // cout<<"instance!"<<endl;

}

void Earth::Startup(){


}
vec3 Earth::Rayhit(vec3 dir){
    mat4 Model;
    Model=translate(Model,transform.Position);
    Model=scale(Model,transform.Scale*1.01f);
    // Model=rotate(Model,radians(transform.Rotation.z),vec3(0.f,0.f,1.f));
    // Model=rotate(Model,radians(transform.Rotation.y),vec3(0.f,1.f,0.f));
    // Model=rotate(Model,radians(transform.Rotation.x),vec3(1.f,0.f,0.f));
    return mesh.Rayhit(this->lookCamera.Postion,dir,Model);
}
void Earth::Instance(FpsCamera& camera,mat4 projection){
    // cout<<"earth instance"<<endl;
    glStencilFunc(GL_ALWAYS,2,0xFF);
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
