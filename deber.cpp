// GLEW ????? ?????????? ?? GLFW.
// GLEW
#include "Game.h"


// World space positions of our cubes

    
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 camFrac = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat s = -90.0f;
GLfloat d = 0.0f;
GLfloat lastX = 400.0, lastY = 300.0;
bool firstmouse = true;

GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;

bool keys[1024];



// Func.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void move();


int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -2;

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    bool g = glewInit();


	if (g != GLEW_OK)
	{
    	std::cout << "Failed to initialize GLEW" << std::endl;
    	return -1;
	}

	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
    lastX = width / 2;
    lastY = height / 2;

	glViewport(0, 0, width, height);

	Shader *prg = new Shader("E:\\vuulps\\Vuulps_Game\\x64\\Debug\\vertex2.glsl", "E:\\vuulps\\Vuulps_Game\\x64\\Debug\\fragment2.glsl");
    Shader* prg2 = new Shader("E:\\vuulps\\Vuulps_Game\\x64\\Debug\\vertex.glsl", "E:\\vuulps\\Vuulps_Game\\x64\\Debug\\fragment.glsl");

	Texture *tex = new SimpleTexture("E:\\vuulps\\Vuulps_Game\\x64\\Debug\\container001-grey.png");
	Mesh *obj = new RectangleMesh(1.5f, 1.5f, 1.5f);
    obj->Load();

    Texture* tex3 = new SimpleTexture("E:\\vuulps\\Vuulps_Game\\x64\\Debug\\container001-grey.png");
    Mesh* obj3 = new RectangleMesh(4.1f, 4.1f, 4.1f);
    obj3->Load();

    Shader* sky = new Shader("E:\\vuulps\\Vuulps_Game\\x64\\Debug\\vertexSKY.glsl", "E:\\vuulps\\Vuulps_Game\\x64\\Debug\\fragmentSKY.glsl");
    
    const char* paths[6] = { "E:\\skybox\\right.jpg",
    "E:\\skybox\\left.jpg",
    "E:\\skybox\\top.jpg",
    "E:\\skybox\\bottom.jpg",
    "E:\\skybox\\front.jpg",
    "E:\\skybox\\back.jpg" };

    Texture* skyTex = new CubeTexture(paths);
    Mesh* skyMesh = new SkyboxMesh();
    skyMesh->Load();

    Object* r = new Object(obj, prg, tex);
    Object* r3 = new Object(obj3, prg, tex3);
    Object* r4 = new Object(obj3, prg2, tex3);

	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 model(1.0f);
	vec = model * vec;

	glm::mat4 view(1.0f);
	view = glm::lookAt(camPos, camPos + camFrac, camUp);

	glm::mat4 projection(1.0f);
	float h = height, w = width;
	if(h != 0)
	{
		projection = glm::perspective(360.0f, w/h, 0.1f, 100.0f);
	}


	

  	glEnable(GL_DEPTH_TEST);
  	glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        /* Swap front and back buffers */
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        move();

        glfwGetFramebufferSize(window, &width, &height);
        
        glViewport(0, 0, width, height);
        h = height;
		w = width;
        if(h != 0)
		{
			projection = glm::perspective(45.0f, w/h, 0.1f, 120.0f);
		}
		view = glm::lookAt(camPos, camPos + camFrac, camUp);

		
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 0.6f, 0.99f, 1.0f);

        glm::mat4 model1 = glm::mat4(1.0f);

        model1 = glm::translate(model1, glm::vec3(5.0f, 25.0f, 0.0f));

        r->render(model1, projection, view);

        glm::mat4 model2 = glm::mat4(1.0f);

        model2 = glm::translate(model2, glm::vec3(5.0f, 10.0f, 0.0f));

        r3->render(model2, projection, view);

        glm::mat4 model3 = glm::mat4(1.0f);

        model3 = glm::translate(model3, glm::vec3(-10.0f, 0.0f, 0.0f));

        r4->render(model3, projection, view);

        
       

        // skybox->render();
        //skybox->render(glm::mat4(1.0f), projection, view);


        glfwSwapBuffers(window);
        
    }

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstmouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstmouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.10f;
    
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    s += xoffset;
    d += yoffset;

    std::cout << camPos.x << " " << camPos.y << " " << camPos.z << std::endl;

    if (d > 89.0f)
        d = 89.0f;
    if (d < -89.0f)
        d = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(s)) * cos(glm::radians(d));
    front.y = sin(glm::radians(d));
    front.z = sin(glm::radians(s)) * cos(glm::radians(d));
    camFrac = glm::normalize(front);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
 
    if (action == GLFW_PRESS)
        keys[key] = true;
    if (action == GLFW_RELEASE)
        keys[key] = false;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	
}
void move()
{
    GLfloat cameraSpeed = 10.0f * deltaTime;
    if (keys[GLFW_KEY_W])
        camPos += cameraSpeed * camFrac;
    if (keys[GLFW_KEY_S])
        camPos -= cameraSpeed * camFrac;
    if (keys[GLFW_KEY_A])
        camPos -= glm::normalize(glm::cross(camFrac, camUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        camPos += glm::normalize(glm::cross(camFrac, camUp)) * cameraSpeed;
}
