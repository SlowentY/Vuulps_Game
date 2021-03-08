#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <gl/Glaux.h>
// GLFW
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <SOIL/SOIL.h>

#define class struct

#ifndef SHADER_H
#define SHADER_H


class Shader{
	private:
		const GLchar *fs, *vs;
		GLuint Frag, Vert;
	public:
		GLuint Prg;
		Shader(const char* vp, const char* fp);
		void Use();
		void Unset();
		void Uniform(const char* name, glm::mat4 mat);
		void Uniform(const char* name, float data);
		void Uniform(const char* name, int data);
		void Uniform(const char* name, glm::vec3 data);
};

GLuint load_img(const char* path);

class Texture{
	protected:
		GLuint textureID;
		unsigned char* data;
		int height, width;
	public:
		Texture(const char* path);
		Texture();
		virtual void Set() = 0;
		Texture* Self();
		virtual void Unset() = 0;
};
class CubeTexture : public Texture {
	public:
		CubeTexture(const char* cubeMapPath[6]);
		void Set() override;
		void Unset() override;
};
class SimpleTexture : public Texture {
	public:
		SimpleTexture(const char* path);
		void Set() override;
		void Unset() override;
};
#endif
