#include"Mesh.hpp"

Mesh::Mesh(vector<Vertex>vertices,vector<GLuint>indics,vector<Texture>textures){
    this->vertices=vertices;
    this->indics=indics;
    this->textures=textures;

    setupMesh();
}

void Mesh::setupMesh(){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD,Mesh init Failed..."<<endl;
        return ;
    }
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Texcoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indics.size()*sizeof(GLuint),&indics[0],GL_STATIC_DRAW);

    glBindVertexArray(0);

    vector<Pixel_Triangle>pixels;
    float maxX=vertices[indics[0]].Position.x,maxY=vertices[indics[0]].Position.y
    ,maxZ=vertices[indics[0]].Position.z,minX=vertices[indics[0]].Position.x
    ,minY=vertices[indics[0]].Position.y,minZ=vertices[indics[0]].Position.z;
    for(int i=0;i<=indics.size()-3;i=i+3){
        Pixel_Triangle triangle;
        triangle.point1=vertices[indics[i]].Position;
        triangle.point2=vertices[indics[i+1]].Position;
        triangle.point3=vertices[indics[i+2]].Position;
        for(int j=0;j<3;j++){
            vec3 tmp=vertices[indics[i+j]].Position;
            if(tmp.x>maxX)maxX=tmp.x;
            else if(tmp.x<minX)minX=tmp.x;
            if(tmp.y>maxY)maxY=tmp.y;
            else if(tmp.y<minY)minY=tmp.y;
            if(tmp.z>maxZ)maxZ=tmp.z;
            else if(tmp.z<minZ)minZ=tmp.z;
        }
        pixels.push_back(triangle);
    }
    this->pixels=pixels;
    vec3 maxpoint(maxX,maxY,maxZ);
    vec3 minpoint(minX,minY,minZ);
    BVHNode*root=new BVHNode();
    root->Bounding_box[0]=maxpoint;
    root->Bounding_box[1]=minpoint;
    this->root=root;
    initBVHTree(this->root,pixels,5);
    // cout<<"iniBVH finished..."<<endl;
    // cout<<pixels.size()<<" "<<indics.size()/3<<endl;

    // cout<<indics.size()%3<<endl;


}
void Mesh::Draw(const Shader& shader){
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD,Drawing Failed..."<<endl;
        return ;
    }
    unsigned int diffuseNr=1;
    unsigned int specularNr=1;
    unsigned int normalNr=1;
    unsigned int heightNr=1;
    unsigned int n=static_cast<unsigned int>(this->textures.size());
    for(unsigned int i=0;i<n;i++){
        glActiveTexture(GL_TEXTURE0+i);
        string type=textures[i].type;
        string name="";
        if(type=="texture_diffuse"){
            name+=(type+to_string(diffuseNr++));
        }
        if(type=="texuture_specular"){
            name+=(type+to_string(specularNr++));
        }
        if(type=="texture_normal"){
            name+=(type+to_string(normalNr++));
        }
        if(type=="texture_height"){
            name+=(type+to_string(heightNr++));
        }
        glBindTexture(GL_TEXTURE_2D,textures[i].id);
        // cout<<"loaded texture: "<<textures[i].id<<endl;
        shader.setInt(name.c_str(),i);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawElements(GL_TRIANGLES,static_cast<unsigned int>(indics.size()),GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    
}
void Mesh::Draw(const Shader& shader,int amount) {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD,Drawing Failed..."<<endl;
        return ;
    }
    unsigned int diffuseNr=1;
    unsigned int specularNr=1;
    unsigned int normalNr=1;
    unsigned int heightNr=1;
    unsigned int n=static_cast<unsigned int>(this->textures.size());
    for(unsigned int i=0;i<n;i++){
        glActiveTexture(GL_TEXTURE0+i);
        string type=textures[i].type;
        string name="";
        if(type=="texture_diffuse"){
            name+=(type+to_string(diffuseNr++));
        }
        if(type=="texuture_specular"){
            name+=(type+to_string(specularNr++));
        }
        if(type=="texture_normal"){
            name+=(type+to_string(normalNr++));
        }
        if(type=="texture_height"){
            name+=(type+to_string(heightNr++));
        }
        glBindTexture(GL_TEXTURE_2D,textures[i].id);
        // cout<<"loaded texture: "<<textures[i].id<<endl;
        shader.setInt(name.c_str(),i);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // glDrawElements(GL_TRIANGLES,static_cast<unsigned int>(indics.size()),GL_UNSIGNED_INT,(void*)0);
    glDrawElementsInstanced(GL_TRIANGLES,static_cast<unsigned int>(indics.size()),GL_UNSIGNED_INT,(void*)0,amount);
    glBindVertexArray(0);
}
void Mesh::initBVHTree(BVHNode*node,vector<Pixel_Triangle>&pixels,int nodeCapacity){
    if(pixels.size()<=nodeCapacity){
        node->objects=pixels;
        return;
    }
    float xaisx,yaisx,zaisx;
    xaisx=node->Bounding_box[0].x-node->Bounding_box[1].x;
    yaisx=node->Bounding_box[0].y-node->Bounding_box[1].y;
    zaisx=node->Bounding_box[0].z-node->Bounding_box[1].z;
    float maxaisx=max({xaisx,yaisx,zaisx});
    if((maxaisx-xaisx)<0.00001){
        sort(pixels.begin(),pixels.end(),[](Pixel_Triangle&a,Pixel_Triangle&b){return a.point1.x<b.point1.x;});
        int mid=pixels.size()/2;
        vector<Pixel_Triangle>left,right;
        for(int i=0;i<mid;i++){
            left.push_back(pixels[i]);
        }
        for(int i=mid;i<pixels.size();i++){
            right.push_back(pixels[i]);
        }
        BVHNode *leftNode=new BVHNode(),*rightNode=new BVHNode();
        rightNode->objects=right;
        rightNode->Bounding_box={node->Bounding_box[0],vec3(pixels[mid].point1.x,node->Bounding_box[1].y,node->Bounding_box[1].z)};
        node->right=rightNode;
        leftNode->Bounding_box={vec3(pixels[mid].point1.x,node->Bounding_box[0].y,node->Bounding_box[0].z),node->Bounding_box[1]};
        node->left=leftNode;
        initBVHTree(node->left,left,nodeCapacity);
        return;
    }
    if((maxaisx-yaisx)<0.00001){
        sort(pixels.begin(),pixels.end(),[](Pixel_Triangle&a,Pixel_Triangle&b){return a.point1.y<b.point1.y;});
        int mid=pixels.size()/2;
        vector<Pixel_Triangle>left,right;
        for(int i=0;i<mid;i++){
            left.push_back(pixels[i]);
        }
        for(int i=mid;i<pixels.size();i++){
            right.push_back(pixels[i]);
        }
        BVHNode *leftNode=new BVHNode(),*rightNode=new BVHNode();
        rightNode->objects=right;
        rightNode->Bounding_box={node->Bounding_box[0],vec3(node->Bounding_box[1].x,pixels[mid].point1.y,node->Bounding_box[1].z)};
        node->right=rightNode;
        leftNode->Bounding_box={vec3(node->Bounding_box[0].x,pixels[mid].point1.y,node->Bounding_box[0].z),node->Bounding_box[1]};
        node->left=leftNode;
        initBVHTree(node->left,left,nodeCapacity);
        return;
        
    }
    if((maxaisx-zaisx)<0.00001){
        sort(pixels.begin(),pixels.end(),[](Pixel_Triangle&a,Pixel_Triangle&b){return a.point1.z<b.point1.z;});
        int mid=pixels.size()/2;
        vector<Pixel_Triangle>left,right;
        for(int i=0;i<mid;i++){
            left.push_back(pixels[i]);
        }
        for(int i=mid;i<pixels.size();i++){
            right.push_back(pixels[i]);
        }
        BVHNode *leftNode=new BVHNode(),*rightNode=new BVHNode();
        rightNode->objects=right;
        rightNode->Bounding_box={node->Bounding_box[0],vec3(node->Bounding_box[1].x,node->Bounding_box[1].y,pixels[mid].point1.z)};
        node->right=rightNode;
        leftNode->Bounding_box={vec3(node->Bounding_box[0].x,node->Bounding_box[0].y,pixels[mid].point1.z),node->Bounding_box[1]};
        node->left=leftNode;
        initBVHTree(node->left,left,nodeCapacity);
        return;
    }
}
BVHNode* Mesh::getBVHTree(){

    return this->root;
}
void Mesh::initalMatrics(){
    glBindVertexArray(VAO);
    glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE,4*sizeof(vec4),(void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4,4,GL_FLOAT,GL_FALSE,4*sizeof(vec4),(void*)(sizeof(vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5,4,GL_FLOAT,GL_FALSE,4*sizeof(vec4),(void*)(2*sizeof(vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6,4,GL_FLOAT,GL_FALSE,4*sizeof(vec4),(void*)(3*sizeof(vec4)));
    glEnableVertexAttribArray(6);

    glVertexAttribDivisor(3,1);
    glVertexAttribDivisor(4,1);
    glVertexAttribDivisor(5,1);
    glVertexAttribDivisor(6,1);

    glBindVertexArray(0);
}