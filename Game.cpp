#include "Game.h"

void Mesh::Render()
{
    
    glDepthFunc(GL_LESS);
    

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
Mesh::Mesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}
RectangleMesh::RectangleMesh(GLfloat l, GLfloat h, GLfloat w) : Mesh()
{
    weight = w;
    lenght = l;
    height = h;
}

void RectangleMesh::Load()
{
    GLfloat p[] = {
    -lenght, -height, -weight,  0.0f, 0.0f,
     lenght, -height, -weight,  1.0f, 0.0f,
     lenght,  height, -weight,  1.0f, 1.0f,
     lenght, height, -weight,  1.0f, 1.0f,
     -lenght, height, -weight,  0.0f, 1.0f,
     -lenght,  -height, -weight,  0.0f, 0.0f,

     -lenght, -height, weight,  0.0f, 0.0f,
     lenght, -height, weight,  1.0f, 0.0f,
     lenght,  height, weight,  1.0f, 1.0f,
     lenght, height, weight,  1.0f, 1.0f,
     -lenght, height, weight,  0.0f, 1.0f,
     -lenght,  -height, weight,  0.0f, 0.0f,

     -lenght, height, weight,  0.0f, 0.0f,
     -lenght, height, -weight,  1.0f, 0.0f,
     -lenght,  -height, -weight,  1.0f, 1.0f,
     -lenght, -height, -weight,  1.0f, 1.0f,
     -lenght, -height, weight,  0.0f, 1.0f,
     -lenght,  height, weight,  0.0f, 0.0f,

     lenght, height, weight,  0.0f, 0.0f,
     lenght, height, -weight,  1.0f, 0.0f,
     lenght,  -height, -weight,  1.0f, 1.0f,
     lenght, -height, -weight,  1.0f, 1.0f,
     lenght, -height, weight,  0.0f, 1.0f,
     lenght,  height, weight,  0.0f, 0.0f,

     -lenght, -height, -weight,  0.0f, 0.0f,
     lenght, -height, -weight,  1.0f, 0.0f,
     lenght,  -height, weight,  1.0f, 1.0f,
     lenght, -height, weight,  1.0f, 1.0f,
     -lenght, -height, weight,  0.0f, 1.0f,
     -lenght,  -height, -weight,  0.0f, 0.0f,

     -lenght, height, -weight,  0.0f, 0.0f,
     lenght, height, -weight,  1.0f, 0.0f,
     lenght,  height, weight,  1.0f, 1.0f,
     lenght, height, weight,  1.0f, 1.0f,
     -lenght, height, weight,  0.0f, 1.0f,
     -lenght,  height, -weight,  0.0f, 0.0f };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
SkyboxMesh::SkyboxMesh() : Mesh()
{
}
void SkyboxMesh::Render()
{
    glDepthFunc(GL_LEQUAL);
    

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
void SkyboxMesh::Load()
{
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
Object::Object(Mesh* m, Shader* s, Texture* tex)
{
    texture = tex;
    shader = s;
    mesh = m;
}
void Object::resetShader(Shader* s)
{
    shader = s;
}
void Object::render(glm::mat4 m, glm::mat4 p, glm::mat4 v)
{
    
    shader->Use();
    
    shader->Uniform("model", m);
    shader->Uniform("view", v);
    shader->Uniform("projection", p);

    texture->Set();
    mesh->Render();

    
}