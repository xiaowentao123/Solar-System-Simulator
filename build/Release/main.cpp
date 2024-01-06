#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<rapidjson/document.h>
#include<rapidjson/writer.h>
#include<rapidjson/stringbuffer.h>
#include<map>
#include<algorithm>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include"FPSCamera.hpp"
#include"Mesh.hpp"
#include"Model.hpp"
#include"Shader.hpp"
#include"stb_image.h"
#include"Utils.hpp"
#include"Earth.hpp"
#include"Object.hpp"
#include"SkyBox.hpp"
#include"Sun.hpp"
#include"Mercury.hpp"
#include"Venus.hpp"
#include"Mars.hpp"
#include"Jupiter.hpp"
#include"Saturn.hpp"
#include"Uranus.hpp"
#include"Neptune.hpp"
#include"Moon.hpp"
#include"Rock.hpp"
using namespace std;
using namespace rapidjson;
FpsCamera camera;
float curTime=0.f,lastTime=0.f;
float lastX,lastY;
bool firstEnter=true;
int screenWidth=1200,screenHeight=800;
double Xpos=0.0,Ypos=0.0;
bool buttondown=false;
bool buttonrightdown=false;
float DeltaTime;
float XOFFSET,YOFFSET;
float scrollY=0.f;
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void proccessInput(GLFWwindow*window,float deltatime);
void mouse_callback(GLFWwindow* window,double xpos,double ypos);
void mouse_button_callback(GLFWwindow*window,int button,int action,int mods);
void mouse_scroll_callback(GLFWwindow*window,double xoffset,double yoffset);
int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES,4);
    
    GLFWwindow* window=glfwCreateWindow(screenWidth,screenHeight,"Solar System Simulator",NULL,NULL);
    if(window==NULL){
        cout<<"Failed to Create GLFW Window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD"<<endl;
        return -1;
    }

    GLFWmonitor* primaryMonitor=glfwGetPrimaryMonitor();

    int xp,yp,w,h;
    glfwGetMonitorWorkarea(primaryMonitor,&xp,&yp,&w,&h);
    int windowX=xp+(w-screenWidth)/2;
    int windowY=yp+(h-screenHeight)/2;
    glfwSetWindowPos(window,windowX,windowY);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetScrollCallback(window,mouse_scroll_callback);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io=ImGui::GetIO();

    io.ConfigFlags|=ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags|=ImGuiConfigFlags_NavEnableGamepad;
    // io.Fonts->AddFontFromFileTTF("",12);

    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init();

    ImGuiWindowFlags windowflags=0;
    windowflags|=ImGuiWindowFlags_NoCollapse;
    windowflags|=ImGuiWindowFlags_NoResize;
    windowflags|=ImGuiWindowFlags_NoMove;
    // windowflags|=ImGuiWindowFlags_NoTitleBar;
    windowflags|=ImGuiWindowFlags_NoScrollbar;
    windowflags|=ImGuiWindowFlags_NoScrollWithMouse;

    ImGuiWindowFlags mainWindowFlags=0;
    mainWindowFlags|=ImGuiWindowFlags_NoResize;
    mainWindowFlags|=ImGuiWindowFlags_NoMove;
    // mainWindowFlags|=ImGuiWindowFlags_NoCollapse;

    ImGuiWindowFlags fpsWindowFlags=0;
    fpsWindowFlags|=ImGuiWindowFlags_NoCollapse;
    fpsWindowFlags|=ImGuiWindowFlags_NoResize;
    fpsWindowFlags|=ImGuiWindowFlags_NoMove;
    fpsWindowFlags|=ImGuiWindowFlags_NoTitleBar;
    fpsWindowFlags|=ImGuiWindowFlags_NoScrollbar;
    fpsWindowFlags|=ImGuiWindowFlags_NoScrollWithMouse;

    ImGuiFocusedFlags helperWindowFlags=0;
    helperWindowFlags|=ImGuiWindowFlags_NoResize;

    ImGuiStyle& style=ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg]=ImVec4(0.f,0.f,0.f,1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);
    // glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    Shader shader_earth("Shaders\\vertex.glsl","Shaders\\earth.glsl");
    Shader shader_light("Shaders\\vertex.glsl","Shaders\\light.glsl");
    Shader shader_skybox("Shaders\\vertex_skybox.glsl","Shaders\\skybox.glsl");
    Shader shader_common("Shaders\\vertex.glsl","Shaders\\fragment_model.glsl");
    Shader shader_rock("Shaders\\vertex_rock.glsl","Shaders\\earth.glsl");

    string PATH_MOON="moon\\Moon_2K.obj";
    Model model_moon(PATH_MOON.data());
    Moon moon(model_moon);
    
    string PATH_EARTH="earth\\Earth_2K.obj";
    Model model_earth(PATH_EARTH.data());

    Model model_light(PATH_EARTH.data());
    Earth earth(model_earth,&moon);
    Earth earh_2(model_earth,&moon);

    string PATH_SUN="Sun\\scene.gltf";
    Model model_sun(PATH_SUN.data());
    Sun sun(model_sun);

    string PATH_MERCURY="Mercury\\scene.gltf";
    Model model_mercury(PATH_MERCURY.data());
    Mercury mercury(model_mercury);

    string PATH_VENUS="venus\\scene.gltf";
    Model model_venus(PATH_VENUS.data());
    Venus venus(model_venus);

    string PATH_MARS="Mars\\Mars_2K.obj";
    Model model_mars(PATH_MARS.data());
    Mars mars(model_mars);

    string PATH_JUPITER="jupiter\\scene.gltf";
    Model model_jupiter(PATH_JUPITER.data());
    Jupiter jupiter(model_jupiter);

    string PATH_SATURN="saturn\\scene.gltf";
    Model model_saturn(PATH_SATURN.data());
    Saturn saturn(model_saturn);

    string PAHT_URANUS="uranus\\scene.gltf";
    Model model_uranus=(PAHT_URANUS.data());
    Uranus uranus(model_uranus);

    string PATH_NEPTUNE="neptune\\scene.gltf";
    Model model_neptune=(PATH_NEPTUNE.data());
    Neptune neptune(model_neptune);

    string PATH_ROCK="Rock\\rock.obj";
    Model model_rock=(PATH_ROCK.data());
    Rock rock(model_rock);

    camera=FpsCamera(vec3(-197.f,55.f,127.f));
    camera.Front=normalize(vec3(0.98292f,-0.175367f,-0.0558119f));
    camera.yaw=-3.24987f;
    camera.pitch=-10.1f;

    Light light;
    Light_parallel light_parallel;
    vec3 lightColor=vec3(1.f);
    vec3 lightPos=sun.transform.Position;
    light.position=lightPos;
    float constrant=1.f;
    float linear=0.045f;
    float quadratic=0.0075f;
    light.ambient=lightColor*0.1f;
    light.diffuse=lightColor*0.5f;
    light.specular=lightColor;
    light.constant=constrant;
    light.linear=linear;
    light.quadratic=quadratic;
    vector<string>light_names={"light.position","light.ambient","light.diffuse","light.specular","light.constrant","light.linear","light.quadratic"};
    
    light_parallel.direction=normalize(-lightPos);
    light_parallel.ambient=lightColor*0.1f;
    light_parallel.diffuse=lightColor*0.5f;
    light_parallel.specular=lightColor;
    vector<string>light_names_p={"light_parallel.direction","light_parallel.ambient","light_parallel.diffuse","light_parallel.specular"};
    
    shader_earth.use();
    shader_earth.setLight(light_names,light);
    shader_earth.setLight(light_names_p,light_parallel);
    shader_earth.setVec3("ViewPos",camera.Postion);
    earth.shader=shader_earth;

    mercury.shader=shader_earth;

    venus.shader=shader_earth;

    mars.shader=shader_earth;

    jupiter.shader=shader_earth;

    saturn.shader=shader_earth;

    uranus.shader=shader_earth;

    neptune.shader=shader_earth;

    moon.shader=shader_earth;

    shader_rock.use();
    shader_rock.setLight(light_names,light);
    shader_rock.setLight(light_names_p,light_parallel);
    shader_rock.setVec3("ViewPos",camera.Postion);

    vector<Object*> objects;
    
    objects.push_back(&sun);
    objects.push_back(&mercury);
    objects.push_back(&venus);
    objects.push_back(&earth);
    objects.push_back(&mars);
    objects.push_back(&jupiter);
    objects.push_back(&saturn);
    objects.push_back(&uranus);
    objects.push_back(&neptune);
    objects.push_back(&moon);

    vector<string>faces_space={
        ".\\Skybox_space\\right.png",
        ".\\Skybox_space\\left.png",
        ".\\Skybox_space\\top.png",
        ".\\Skybox_space\\bottom.png",
        ".\\Skybox_space\\front.png",
        ".\\Skybox_space\\back.png"
    };
    unsigned int texuture_cube=Utils::loadCubemap(faces_space);
    SkyBox skybox(faces_space);

    unsigned int FBO;
    glGenFramebuffers(1,&FBO);
    unsigned int texture_pic;
    unsigned int RBO;
    glGenTextures(1,&texture_pic);
    glGenRenderbuffers(1,&RBO);

    glBindTexture(GL_TEXTURE_2D,texture_pic);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,2048,2048,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    glBindRenderbuffer(GL_RENDERBUFFER,RBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,2048,2048);
    glBindRenderbuffer(GL_RENDERBUFFER,0);

    glBindFramebuffer(GL_FRAMEBUFFER,FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture_pic,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,RBO);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
        cout<<"framebuffer is not completed!"<<endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glStencilFunc(GL_ALWAYS,1,0xFF);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glStencilMask(0xFF);

    FpsCamera camera2(vec3(0.f,0.f,10.f));
    
    float pitch=0.f,yaw=0.f;

    map<string,vec3>targetoffset;
    targetoffset["Earth"]=vec3(0.f,0.f,10.f);
    targetoffset["Sun"]=vec3(0.f,0.f,100.f);
    targetoffset["Mercury"]=vec3(0.f,0.f,5.f);
    targetoffset["Venus"]=vec3(0.f,0.f,10.f);
    targetoffset["Mars"]=vec3(0.f,0.f,10.f);
    targetoffset["Jupiter"]=vec3(0.f,0.f,35.f);
    targetoffset["Saturn"]=vec3(0.f,0.f,35.f);
    targetoffset["Uranus"]=vec3(0.f,0.f,20.f);
    targetoffset["Neptune"]=vec3(0.f,0.f,20.f);
    targetoffset["Moon"]=vec3(0.f,0.f,2.f);

    map<string,vec3>camera2Pos;
    camera2Pos["Earth"]=vec3(0.f,0.f,10.f);
    camera2Pos["Sun"]=vec3(0.f,0.f,30.f);
    camera2Pos["Mercury"]=vec3(0.f,0.f,3.0f);
    camera2Pos["Venus"]=vec3(0.f,0.f,3.f);  
    camera2Pos["Mars"]=vec3(0.f,0.f,10.5f);
    camera2Pos["Jupiter"]=vec3(0.f,0.f,3.f);
    camera2Pos["Saturn"]=vec3(0.f,0.f,650.f);
    camera2Pos["Uranus"]=vec3(0.f,0.f,5.f);
    camera2Pos["Neptune"]=vec3(0.f,0.f,3.f);
    camera2Pos["Moon"]=vec3(0.f,0.f,5.f);

    vector<string>jsonPaths={
        "Text\\Sun.json",
        "Text\\Mercury.json",
        "Text\\Venus.json",
        "Text\\Earth.json",
        "Text\\Mars.json",
        "Text\\Jupiter.json",
        "Text\\Saturn.json",
        "Text\\Uranus.json",
        "Text\\Neptune.json",
        "Text\\asteroids.json",
        "Text\\Moon.json"
    };

    map<string,Object*>objects_m;
    objects_m.emplace(pair<string,Object*>("Sun",&sun));
    objects_m.emplace(pair<string,Object*>("Mercury",&mercury));
    objects_m.emplace(pair<string,Object*>("Venus",&venus));
    objects_m.emplace(pair<string,Object*>("Earth",&earth));
    objects_m.emplace(pair<string,Object*>("Mars",&mars));
    objects_m.emplace(pair<string,Object*>("Jupiter",&jupiter));
    objects_m.emplace(pair<string,Object*>("Saturn",&saturn));
    objects_m.emplace(pair<string,Object*>("Uranus",&uranus));
    objects_m.emplace(pair<string,Object*>("Neptune",&neptune));
    objects_m.emplace(pair<string,Object*>("Moon",&moon));
    
    int mainWindow_w=0.25f*screenWidth,mainWindow_h=0.8f*screenHeight;
    int amount=100000;
    bool isopen=true;
    mat4* matrics=Utils::loadMatrices(amount,400.f,25.f);
    rock.mesh.initalMeshMatrics(matrics,amount);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        // cout<<"FPS: "<<(int)(1.f/DeltaTime)<<endl;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //Main menu
        {
            ImGui::Begin("Main Menu",0,mainWindowFlags);
            ImGui::SetWindowPos(ImVec2(screenWidth-1.f*mainWindow_w,0.1*screenHeight));
            ImGui::SetWindowSize(ImVec2(mainWindow_w,mainWindow_h));
            static string clickobject="";
            for(int i=0;i<jsonPaths.size();i++){
            ifstream file(jsonPaths[i]);
            if(!file.is_open()){
                cout<<"failed to open file"<<endl;
            }

            string jsonstr((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
            file.close();

            Document document;
            document.Parse(jsonstr.c_str());

            if(document.HasParseError()){
                cout<<"error!"<<endl;
            }

            string name=document["Name"].GetString();
            string diameter=document["Diameter"].GetString();
            string volume=document["Volume"].GetString();
            string mass=document["Mass"].GetString();
            string introduction=document["Introduction"].GetString();
            if(ImGui::CollapsingHeader(name.c_str())){
                ImGui::Text("Name: ");
                ImGui::SameLine();
                ImGui::Text(name.c_str());

                ImGui::NewLine();

                ImGui::Columns(2,"",false);
                ImGui::SetColumnWidth(0,0.3f*ImGui::GetWindowWidth());
                ImGui::SetColumnWidth(1,0.7f*ImGui::GetWindowWidth());
                ImGui::Text("Radis");
                ImGui::NextColumn();
                ImGui::ProgressBar(1.f,ImVec2(0.f,0.f),diameter.c_str());
                ImGui::Columns(1);

                ImGui::Columns(2,"",false);
                ImGui::SetColumnWidth(0,0.3f*ImGui::GetWindowWidth());
                ImGui::SetColumnWidth(1,0.7f*ImGui::GetWindowWidth());
                ImGui::Text("Volume");
                ImGui::NextColumn();
                ImGui::ProgressBar(1.f,ImVec2(0.f,0.f),volume.c_str());
                ImGui::Columns(1);

                ImGui::Columns(2,"",false);
                ImGui::SetColumnWidth(0,0.3f*ImGui::GetWindowWidth());
                ImGui::SetColumnWidth(1,0.7f*ImGui::GetWindowWidth());
                ImGui::Text("Quality");
                ImGui::NextColumn();
                ImGui::ProgressBar(1.f,ImVec2(0.f,0.f),mass.c_str());
                ImGui::Columns(1);

                ImGui::NewLine();

                ImGui::Text("Introduction");
                ImGui::TextWrapped(introduction.c_str());
                string buttonText="Check the "+name+"!";
                if(ImGui::Button(buttonText.c_str())){
                    if(name!="Asteroids"){
                         if(clickobject!=""){
                        objects_m[clickobject]->isClickOn=false;
                    }
                    clickobject=name;
                    objects_m[name]->isClickOn=true;
                    camera.isMove=true;
                    camera.isLock=true;
                    camera.moveTarget=objects_m[name]->transform.Position+targetoffset[objects_m[name]->ObjectName];
                    }else{
                        camera.isMove=true;
                        camera.isLock=true;
                        camera.moveTarget=vec3(211.f,5.f,307.f);
                    }
                   
                }
                
            }
            
        }

        ImGui::End();
        }

        //Fps Show
        {
            int fpsValue=(int)(1.f/DeltaTime);
            string fpsStr="FPS: "+to_string(fpsValue);
            ImGui::GetStyle().Colors[ImGuiCol_WindowBg]=ImVec4(0.f,0.f,0.f,0.f);
            ImGui::Begin(" ",0,fpsWindowFlags);
            ImGui::SetWindowPos(ImVec2(0.01*screenWidth,0.01*screenHeight));
            // ImGui::SetWindowSize(ImVec2(mainWindow_w,mainWindow_h));
            ImGui::Text(fpsStr.c_str());
            ImGui::End();
            ImGui::StyleColorsDark();
        }

        //Helper
        {
            ImGui::Begin("Helper",0,helperWindowFlags);
            ImGui::SetWindowPos(ImVec2(0.01*screenWidth,0.1*screenHeight));
            ImGui::SetWindowSize(ImVec2(0.25*screenWidth,0.25*screenWidth));
            ImGui::TextWrapped("1. Use 'W' to move forward, 'A' to move left, 'S' to move backward, and 'D' to move right. Press 'LSHIFT' to move downward, and press 'Space' to move upward.");
            ImGui::TextWrapped("2. Right-clicking and dragging the mouse allows you to rotate the camera view.");
            ImGui::TextWrapped("3. Clicking on an object will focus the camera on that object, while clicking on empty space will cancel the focus.");
            ImGui::TextWrapped("4. After focusing the camera view, clicking on the thumbnail below and right-clicking while dragging inside the thumbnail allows you to rotate the thumbnail.");
            ImGui::TextWrapped("5. Pressing 'LCONTROL' can increase your movement speed.");
            ImGui::End();
        }

        for(auto obj:objects){
            if(obj->isClickOn){
                glBindFramebuffer(GL_FRAMEBUFFER,FBO);
                glViewport(0,0,2048,2048);
                glClearColor(0.0f,0.0f,0.0f,1.f);
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
                shader_common.use();
                mat4 tempModel;
                tempModel=rotate(tempModel,radians(yaw),vec3(0.f,1.f,0.f));
                tempModel=rotate(tempModel,radians(pitch),vec3(1.f,0.f,0.f));
                camera2.Postion=camera2Pos[obj->ObjectName];
                shader_common.setMat4("Model",tempModel);
                shader_common.setMat4("View",camera2.getLooAt());
                shader_common.setMat4("Projection",perspective(radians(obj->POV),1.f,0.1f,500.f));
                // obj.Draw(shader_common);
                obj->mesh.Draw(shader_common);
                glBindFramebuffer(GL_FRAMEBUFFER,0);
                glViewport(0,0,screenWidth,screenHeight);
             
                int window_w=screenWidth*0.20f,window_h=screenWidth*0.20f;
                ImGui::Begin(obj->ObjectName.c_str(),0,windowflags);
                ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(texture_pic)),ImVec2(static_cast<float>(window_w),
                static_cast<float>(window_h)),ImVec2(0.1,0.9),ImVec2(0.9,0.1));
                ImGui::SetWindowPos(ImVec2(screenWidth-2.5*window_w-10,screenHeight-window_h-10));
                ImGui::SetWindowSize(ImVec2(window_w,window_h));

                if(ImGui::IsWindowFocused()){
                    if(ImGui::IsWindowHovered()&&ImGui::IsMouseDown(1)){
                    // cout<<"mouse donw 1"<<endl;
                    // camera2.processMouseInput(XOFFSET,YOFFSET);
                        pitch-=YOFFSET*0.3f;
                        yaw+=XOFFSET*0.3f;
                    }
                    if(ImGui::IsWindowHovered()&&ImGui::GetIO().MouseWheel!=0.0f){
                        float scrollDelta=ImGui::GetIO().MouseWheel;
                        scrollDelta=glm::clamp(scrollDelta,-1.0f,1.0f);
                        obj->POV=glm::clamp(obj->POV+scrollDelta*DeltaTime*60,30.f,60.f);

                        ImGui::GetIO().MouseWheel=0.f;
                    }
                }
                ImGui::End();
            }
        }
        
        curTime=glfwGetTime();
        DeltaTime=curTime-lastTime;
        lastTime=curTime;
        if(!camera.isLock){
            proccessInput(window,DeltaTime);
        }
        

        // cout<<"Xpos: "<<Xpos<<"Ypos: "<<Ypos<<endl;

        
        glClearColor(0.0f,0.0f,0.0f,1.f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        // shader_earth.use();
        mat4 Projection;


        Projection=perspective(radians(60.f),(screenWidth*1.f+0.00001f)/(screenHeight*1.f+0.00001f),0.1f,700.f);
        // model_earth.Draw(shader_earth);
        // earth.Instance(shader_earth,camera,Projection);


        for(auto& obj:objects){
            // obj.shader.use();
            if(obj->ObjectName=="Sun"){
                obj->Instance(shader_common,camera,Projection);
            }else{
              
              obj->Instance(camera,Projection);
            }
            
        }
        shader_rock.use();
        rock.InstanceN(shader_rock,camera,Projection,amount);
        // shader_common.use();
        // rock.Instance(shader_common,camera,Projection);
        
        // earh_2.transform.Position=vec3(0.f,0.f,-3.f);
        // earh_2.Instance(shader_earth,camera,Projection);

        if(buttondown&&!camera.isLock){
            vec3 Ray=Utils::getRay(Xpos,screenHeight-Ypos,screenWidth,screenHeight,Projection,camera);
            vec3 minhitpoint=vec3(100000,0.f,0.f);
            Object* minobject;
            for(auto obj:objects){
                vec3 hitpoint=obj->Rayhit(Ray);
                if(hitpoint!=camera.Postion&&distance(minhitpoint,camera.Postion)>distance(hitpoint,camera.Postion)){

                    minhitpoint=hitpoint;
                    minobject=obj;
                }else{
                    obj->isClickOn=false;
                    yaw=0.f;
                    pitch=0.f;
                }
            }
            if(minhitpoint!=vec3(100000,0.f,0.f)){
                cout<<"click on "<<minobject->ObjectName<<endl;
                minobject->isClickOn=true;
                camera.isMove=true;
                camera.isLock=true;
                camera.moveTarget=minobject->transform.Position+targetoffset[minobject->ObjectName];
            }else{
                cout<<"unclick on"<<endl;
                yaw=0.f;
                pitch=0.f;
            }
            buttondown=false;
        }

        // shader_light.use();
        // mat4 light_Model;
        // light_Model=translate(mat4(1.f),lightPos); 
        // light_Model=scale(light_Model,vec3(0.1f));
        // shader_light.setMat4("Model",light_Model);
        // shader_light.setMat4("View",camera.getLooAt());
        // shader_light.setMat4("Projection",Projection);

        // model_light.Draw(shader_light);

        // earth.Tick(DeltaTime);
        for(auto obj:objects){
            obj->Tick(DeltaTime);
        }
        camera.Tick(DeltaTime);

        shader_skybox.use();
        shader_skybox.setMat4("View",mat4(mat3(camera.getLooAt())));
        shader_skybox.setMat4("Projection",Projection);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,texuture_cube);
        shader_skybox.setInt("skybox",0);
        skybox.DrawBox(shader_skybox);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    screenWidth=width;
    screenHeight=height;
    glViewport(0,0,width,height);
    // cout<<screenWidth<<" "<<screenHeight<<endl;
}
void proccessInput(GLFWwindow*window,float deltatime){
    // cout<<"X: "<<camera.Postion.x<<" "<<"Y: "<<camera.Postion.y<<" "<<"Z: "<<camera.Postion.z<<endl;
    // cout<<"Front: "<<camera.Front.x<<" "<<camera.Front.y<<" "<<camera.Front.z<<endl;
    // cout<<"yaw: "<<camera.yaw<<" "<<"pitch: "<<camera.pitch<<endl;
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS){
        camera.processKeyboradInput(deltatime,FORWARD);
    }
    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
        camera.processKeyboradInput(deltatime,BACK);
    }
    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
        camera.processKeyboradInput(deltatime,LEFT);
    }
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
       camera.processKeyboradInput(deltatime,RIGHT);
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS){
        camera.processKeyboradInput(deltatime,UP);
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS){
        camera.processKeyboradInput(deltatime,DOWN);
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_CONTROL)==GLFW_PRESS){
        camera.speed=50.f;
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_CONTROL)==GLFW_RELEASE){
        camera.speed=10.f;
    }
    
    
}
void mouse_callback(GLFWwindow* window,double xpos,double ypos){
    if(firstEnter){
        lastX=xpos;
        lastY=ypos;
        firstEnter=false;
    }
    float xoffset=xpos-lastX;
    float yoffset=lastY-ypos;

    XOFFSET=xoffset;
    YOFFSET=yoffset;
    // cout<<xoffset<<" "<<yoffset<<endl;
    lastX=xpos;
    lastY=ypos;

    Xpos=xpos;
    Ypos=ypos;
    if(buttonrightdown&&!camera.isLock){
        camera.processMouseInput(xoffset,yoffset);
    }
    
}
void mouse_button_callback(GLFWwindow*window,int button,int action,int mods){
    ImGuiIO& io=ImGui::GetIO();
    if(io.WantCaptureMouse){
        // cout<<"imgui is capturing mouse"<<endl;
        return;
    }
    
    if(button==GLFW_MOUSE_BUTTON_LEFT&&action==GLFW_PRESS){
        // cout<<"click!"<<endl;
        buttondown=true;
    }
    if(button==GLFW_MOUSE_BUTTON_LEFT&&action==GLFW_RELEASE){
        // cout<<"up!"<<endl;
    }
    if(button==GLFW_MOUSE_BUTTON_RIGHT&&action==GLFW_PRESS){
        buttonrightdown=true;
        if(camera.isLock&&!camera.isMove){
            camera.isLock=false;
        }
        // glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    }
    if(button==GLFW_MOUSE_BUTTON_RIGHT&&action==GLFW_RELEASE){
        buttonrightdown=false;
        
        // glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }
}
void mouse_scroll_callback(GLFWwindow*window,double xoffset,double yoffset){
    // cout<<"xoffset: "<<xoffset<<endl;
    // cout<<"yoffset: "<<yoffset<<endl;
    scrollY=std::min(std::max(yoffset,-1.0),1.0);
}