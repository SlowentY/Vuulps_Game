#include "lala.h"

#ifndef SOMETHING_INCLUDED
#define SOMETHING_INCLUDED

class Mesh {
    protected:
        GLuint VAO, VBO;
    public:
        Mesh();
        virtual void Load() = 0;
        virtual void Render();
};

class RectangleMesh : public Mesh {
    private:
        GLfloat weight, height, lenght;
    public:
        RectangleMesh(GLfloat l, GLfloat h, GLfloat w);
        void Load() override;
};
class SkyboxMesh : public Mesh
{
    public :
        SkyboxMesh();
        void Load() override;
        void Render() override;
};

class Object
{
private:
    Mesh* mesh;
    Shader* shader;
    Texture* texture;
public:
    Object(Mesh* m);
    Object(Mesh* m, Shader* s, Texture* tex);
    void render(glm::mat4 m, glm::mat4 p, glm::mat4 v);
    void resetShader(Shader* s);
};
#endif

