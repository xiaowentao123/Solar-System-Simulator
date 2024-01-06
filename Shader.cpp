#include "Shader.hpp"

Shader::Shader(const char* vertexPath,const char*fragmentPath){

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD,Shader init Failed..."<<endl;
        return ;
    }

    //读取文件
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::failbit|ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit|ifstream::badbit);

    try
    {   
        // cout<<vertexPath<<endl;
        // cout<<fragmentPath<<endl;
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream,fShaderStream;
        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode=vShaderStream.str();
        fragmentCode=fShaderStream.str();
    }
    catch(ifstream::failure e)
    {
        cout<<"FILE OPEN FAILED!"<<endl;
        cout<<e.what()<<endl;
    }

    const char*vShaderCode=vertexCode.c_str();
    const char*fShaderCode=fragmentCode.c_str();
    //编译文件

    unsigned int vertex,fragment;
    int success;
    char infoLog[512];
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex,512,NULL,infoLog);
        cout<<"VERTEX SHADER COMPLIE FAILED...\n";
        cout<<infoLog<<endl;
    }
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex,512,NULL,infoLog);
        cout<<"FRAGMENT SHADER COMPLIE FAILED...\n";
        cout<<infoLog<<endl;
    }

    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(ID,512,NULL,infoLog);
        cout<<"PROGRAM LINKED FAILED...\n";
        cout<<infoLog<<endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
Shader::Shader(){
    
}
void Shader::use(){
    glUseProgram(ID);
}
void Shader::setBool(const string&name,bool value) const{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}
void Shader::setInt(const string&name,int value)const{

    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}
void Shader::setFloat(const string&name,float value)const{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}
void Shader::setMat4(const string&name,mat4& matrix)const{
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,value_ptr(matrix));
}
void Shader::setVec3(const string&name,vec3&vector)const{
    glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,value_ptr(vector));
}
void Shader::setMaterial(const vector<string>&names,Material&material)const{
    glUniform3fv(glGetUniformLocation(ID,names[0].c_str()),1,value_ptr(material.ambient));
    glUniform3fv(glGetUniformLocation(ID,names[1].c_str()),1,value_ptr(material.diffuse));
    glUniform3fv(glGetUniformLocation(ID,names[2].c_str()),1,value_ptr(material.specular));
    glUniform1f(glGetUniformLocation(ID,names[3].c_str()),material.shininess);
}
void Shader::setLight(const vector<string>&names,Light&light)const{
    glUniform3fv(glGetUniformLocation(ID,names[0].c_str()),1,value_ptr(light.position));
    glUniform3fv(glGetUniformLocation(ID,names[1].c_str()),1,value_ptr(light.ambient));
    glUniform3fv(glGetUniformLocation(ID,names[2].c_str()),1,value_ptr(light.diffuse));
    glUniform3fv(glGetUniformLocation(ID,names[3].c_str()),1,value_ptr(light.specular));
    glUniform1f(glGetUniformLocation(ID,names[4].c_str()),light.constant);
    glUniform1f(glGetUniformLocation(ID,names[5].c_str()),light.linear);
    glUniform1f(glGetUniformLocation(ID,names[6].c_str()),light.quadratic);
    
}
void Shader::setMaterial(const vector<string>&names,Material_tex&material)const{
    setInt(names[0],material.diffuse);
    setInt(names[1],material.specular);
    setFloat(names[2],material.shiniess);
}
void Shader::setLight(const vector<string>&names,Light_parallel&light)const{
    setVec3(names[0],light.direction);
    setVec3(names[1],light.ambient);
    setVec3(names[2],light.diffuse);
    setVec3(names[3],light.specular);
}
void Shader::setLight(const vector<string>&names,Light_torch&light)const{
    setVec3(names[0],light.position);
    setVec3(names[1],light.direction);
    setFloat(names[2],light.cutOff);
    setFloat(names[3],light.outerCutOff);
    setVec3(names[4],light.ambient);
    setVec3(names[5],light.diffuse);
    setVec3(names[6],light.specular);
    setFloat(names[7],light.constant);
    setFloat(names[8],light.linear);
    setFloat(names[9],light.quadratic);
}
void Shader::setLights(const vector<vector<string>>&names,vector<Light>&lights)const{
    for(int i=0;i<lights.size();i++){
        setLight(names[i],lights[i]);
    }
}
Shader::~Shader(){
    glDeleteProgram(ID);
    // cout<<"xi gou"<<endl;
    // cout<<ID<<endl;
}