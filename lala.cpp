#include "lala.h"

Shader::Shader(const char* vp, const char* fp)
{

	std::fstream vF;
	std::fstream fF;

	vF.open(vp);
	fF.open(fp);


	std::stringstream vStream;
	std::stringstream fStream;

	vStream << vF.rdbuf();
	fStream << fF.rdbuf();

	std::string vss = vStream.str();
	std::string fss = fStream.str();


	std::cout << vss << std::endl;
	std::cout << fss << std::endl;

	vs = vss.c_str();
	fs = fss.c_str();


	Vert = glCreateShader(GL_VERTEX_SHADER);
	std::cout << Vert << std::endl;
	glShaderSource(Vert, 1, &vs, NULL);
	glCompileShader(Vert);
	GLint success;
    GLchar infoLog[512];
    glGetShaderiv(Vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Vert, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    Frag = glCreateShader(GL_FRAGMENT_SHADER);
    std::cout << Frag << std::endl;
    glShaderSource(Frag, 1, &fs, NULL);
    glCompileShader(Frag);
    glGetShaderiv(Frag, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Frag, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    Prg = glCreateProgram();
    std::cout << Prg << std::endl;
    glAttachShader(Prg, Vert);
    glAttachShader(Prg, Frag);
    glLinkProgram(Prg);
    glGetProgramiv(Prg, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(Prg, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(Vert);
    glDeleteShader(Frag);
}

void Shader::Use()
{
	glUseProgram(Prg);
}
void Shader::Uniform(const char* name, glm::mat4 mat)
{
    GLuint Loc = glGetUniformLocation(this->Prg, "projection");
    glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::Uniform(const char* name, float data)
{
    GLuint Loc = glGetUniformLocation(this->Prg, "projection");
    glUniform1fv(Loc, 1, &data);
}

Texture::Texture(const char* path)
{
	data = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

	glGenTextures(1, &textureID);
	// Биндим текстуру, и теперь все функции по работе с текстурами будут работать с этой
}
Texture::Texture()
{
    glGenTextures(1, &textureID);
    // Биндим текстуру, и теперь все функции по работе с текстурами будут работать с этой
}
SimpleTexture::SimpleTexture(const char* path) : Texture(path)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    // Отправляем картинку в OpenGL текстуру
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLint g_nMaxAnisotropy;
    glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &g_nMaxAnisotropy);
    printf("MAX anisotropy: %d\n", g_nMaxAnisotropy);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, g_nMaxAnisotropy - 0.1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void SimpleTexture::Set()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}
Texture* Texture::Self()
{
    return this;
}
void SimpleTexture::Unset()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
CubeTexture::CubeTexture(const char* cubeMapPath[6]) : Texture()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (int i = 0; i < 6; i++)
    {
        data = SOIL_load_image(cubeMapPath[i], &width, &height, 0, SOIL_LOAD_RGBA);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );

            SOIL_free_image_data(data);
        }
        else
        {
            std::cout << "error with loading CubeMap " << i << std::endl;
            SOIL_free_image_data(data);
        }
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
void CubeTexture::Set()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}
void CubeTexture::Unset()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

