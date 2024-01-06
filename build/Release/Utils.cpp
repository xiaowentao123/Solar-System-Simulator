#include "Utils.hpp"

bool Utils::Box3dHit(vec3 ori,vec3 dir,vector<vec3>box){
    dir=normalize(dir);
    float x_max,x_min,y_max,y_min,z_max,z_min;
    x_max=box[0].x,x_min=box[1].x;
    y_max=box[0].y,y_min=box[1].y;
    z_max=box[0].z,z_min=box[1].z;

    float t_x_1,t_x_2,t_y_1,t_y_2,t_z_1,t_z_2;
    
    t_x_1=(x_max-ori.x)/(dir.x+0.00001f);
    t_x_2=(x_min-ori.x)/(dir.x+0.00001f);
    float t_x_in,t_x_out;
    t_x_in=std::min(t_x_1,t_x_2);
    t_x_out=std::max(t_x_1,t_x_2);

    t_y_1=(y_max-ori.y)/(dir.y+0.00001f);
    t_y_2=(y_min-ori.y)/(dir.y+0.00001f);
    float t_y_in,t_y_out;
    t_y_in=std::min(t_y_1,t_y_2);
    t_y_out=std::max(t_y_1,t_y_2);

    t_z_1=(z_max-ori.z)/(dir.z+0.00001f);
    t_z_2=(z_min-ori.z)/(dir.z+0.00001f);
    float t_z_in,t_z_out;
    t_z_in=std::min(t_z_1,t_z_2);
    t_z_out=std::max(t_z_1,t_z_2);

    float t_in,t_out;
    t_in=std::max({t_x_in,t_y_in,t_z_in});
    t_out=std::min({t_x_out,t_y_out,t_z_out});

    if(t_in<t_out&&t_out>0){
        return true;
    }
    return false;

}
bool Utils::TriangleHit(vec3 ori,vec3 dir,vector<vec3>&triangle,vec3&hitpoint){
    vec3 e1,e2,s,s1,s2;
    vec3 p0,p1,p2;
    dir=normalize(dir);
    p0=triangle[0];
    p1=triangle[1];
    p2=triangle[2];

    e1=p1-p0,e2=p2-p0,s=ori-p0;
    s1=cross(dir,e2);
    s2=cross(s,e1);

    vec3 res=(vec3(dot(s2,e2),dot(s1,s),dot(s2,dir))/dot(s1,e1));
    float t=res.x,b1=res.y,b2=res.z;
    if(b1>0&&b2>0&&(b1+b2<1)){
        hitpoint=(1-b1-b2)*p0+b1*p1+b2*p2;
        return true;
    }else{
        hitpoint=(1-b1-b2)*p0+b1*p1+b2*p2;
        return false;
    }
}
vec3 Utils::getRay(float x,float y,int screenWidth,int screenHeight,mat4 projection,FpsCamera camera){
    mat4 viewport=glm::mat4(
        screenWidth/2.f,0.f,0.f,0.f,
        0.f,screenHeight/2.f,0.f,0.f,
        0.f,0.f,1.f,0.f,
        screenWidth/2.f,screenHeight/2.f,0.f,1.f
    );
    vec4 point(x,y,-1.f,1.f);
    point=inverse(camera.getLooAt())*inverse(projection)*inverse(viewport)*point;
    point/=point.w;
    vec3 result;
    result=vec3(point-vec4(camera.Postion,1.f));
    result=normalize(result);
    return result;
}
unsigned int Utils::loadCubemap(vector<string>&faces){
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD,Mesh init Failed..."<<endl;
        return -1;
        }
        unsigned int texture_cube;
        glGenTextures(1,&texture_cube);
        glBindTexture(GL_TEXTURE_CUBE_MAP,texture_cube);

        int width,height,nrChannels;
        for(int i=0;i<faces.size();i++){
            unsigned char*data=stbi_load(faces[i].c_str(),&width,&height,&nrChannels,0);
            // cout<<width<<" "<<height<<endl;
            if(data){
                
                if(nrChannels==3){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
                    stbi_image_free(data);
                }
                else if(nrChannels==4){
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
                    stbi_image_free(data);
                }else{
                    cout<<"no instance channels..."<<endl;
                    cout<<nrChannels<<endl;
                    stbi_image_free(data);
                }
            }else{
                cout<<"cubemap texture  failed to load path:"<<faces[i]<<endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP,0);
        return texture_cube;
}
mat4* Utils::loadMatrices(int amount,float radius,float offset){
    glm::mat4* modelMatrices;
    modelMatrices=new glm::mat4[amount];
    srand(glfwGetTime());
    for(int i=0;i<amount;i++){
        mat4 model;
        float angle=(float)i/(float)amount*360.f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; 
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        float scale=(rand()%20)/100.f+0.05f;
        model=glm::scale(model,glm::vec3(scale));

        float rotAngle=(rand()%360);
        model=rotate(model,rotAngle,vec3(0.4f,0.6f,0.8f));

        modelMatrices[i]=model;
    }
    return modelMatrices;
}