#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"
#include "camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// Размер окна
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// Камера
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Сфера
const GLfloat PI = 3.14159265358979323846f;
const int Y_SEGMENTS = 50;
const int X_SEGMENTS = 50;


float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Куб
glm::vec3 cubePos(0.0f, -4.0f, 0.0f);
// к20
glm::vec3 d20Pos(0.0f, 0.0f, 0.0f);
// Конус
glm::vec3 conePos(4.0f, -5.0f, 4.0f);
// Сфера
glm::vec3 spherePos(4.0f, -3.0f, 4.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab_4", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader Shader("../ConsoleApplication1/shader.vs", "../ConsoleApplication1/shader.fs");

    float vertices[10000] = {
        -5.0f, -5.0f, -5.0f,
         5.0f, -5.0f, -5.0f,
         5.0f,  5.0f, -5.0f,
         5.0f,  5.0f, -5.0f,
        -5.0f,  5.0f, -5.0f,
        -5.0f, -5.0f, -5.0f,

        -5.0f, -5.0f,  5.0f,
         5.0f, -5.0f,  5.0f,
         5.0f,  5.0f,  5.0f,
         5.0f,  5.0f,  5.0f,
        -5.0f,  5.0f,  5.0f,
        -5.0f, -5.0f,  5.0f,

        -5.0f,  5.0f,  5.0f,
        -5.0f,  5.0f, -5.0f,
        -5.0f, -5.0f, -5.0f,
        -5.0f, -5.0f, -5.0f,
        -5.0f, -5.0f,  5.0f,
        -5.0f,  5.0f,  5.0f,

         5.0f,  5.0f,  5.0f,
         5.0f,  5.0f, -5.0f,
         5.0f, -5.0f, -5.0f,
         5.0f, -5.0f, -5.0f,
         5.0f, -5.0f,  5.0f,
         5.0f,  5.0f,  5.0f,

        -5.0f, -5.0f, -5.0f,
         5.0f, -5.0f, -5.0f,
         5.0f, -5.0f,  5.0f,
         5.0f, -5.0f,  5.0f,
        -5.0f, -5.0f,  5.0f,
        -5.0f, -5.0f, -5.0f,

        -5.0f,  5.0f, -5.0f,
         5.0f,  5.0f, -5.0f,
         5.0f,  5.0f,  5.0f,
         5.0f,  5.0f,  5.0f,
        -5.0f,  5.0f,  5.0f,
        -5.0f,  5.0f, -5.0f,

        0.809f, 0.5f, 0.588f,   //1
        0.0f, 1.118f, 0.0f,     //11
        -0.309f, 0.5f, 0.951f,  //3

        -0.309f, 0.5f, 0.951f,  //3
        0.0f, 1.118f, 0.0f,     //11
        -1.0f, 0.5f, 0.0f,      //5

        -1.0f, 0.5f, 0.0f,      //5
        0.0f, 1.118f, 0.0f,     //11
        -0.309f, 0.5f, -0.951f, //7

        -0.309f, 0.5f, -0.951f, //7
        0.0f, 1.118f, 0.0f,     //11
        0.809f, 0.5f, -0.588f,  //9

        0.809f, 0.5f, -0.588f,  //9
        0.0f, 1.118f, 0.0f,     //11
        0.809f, 0.5f, 0.588f,   //1

        0.809f, 0.5f, 0.588f,   //1
        -0.309f, 0.5f, 0.951f,  //3
        0.309f, -0.5f, 0.951f,  //2

        0.309f, -0.5f, 0.951f,  //2
        -0.309f, 0.5f, 0.951f,  //3
        -0.809f, -0.5f, 0.588f,   //4

        -0.309f, 0.5f, 0.951f,  //3
        -1.0f, 0.5f, 0.0f,      //5
        -0.809f, -0.5f, 0.588f,   //4   

        -0.809f, -0.5f, 0.588f,   //4 
        -1.0f, 0.5f, 0.0f,      //5
        -0.809f, -0.5f, -0.588f,   //6

        -1.0f, 0.5f, 0.0f,      //5
        -0.309f, 0.5f, -0.951f, //7
        -0.809f, -0.5f, -0.588f,   //6

        -0.809f, -0.5f, -0.588f,   //6
        -0.309f, 0.5f, -0.951f, //7
        0.309f, -0.5f, -0.951f, //8

        -0.309f, 0.5f, -0.951f, //7
        0.809f, 0.5f, -0.588f,  //9
        0.309f, -0.5f, -0.951f, //8

        0.309f, -0.5f, -0.951f, //8
        0.809f, 0.5f, -0.588f,  //9
        1.0f, -0.5f, 0.0f,      //10

        0.809f, 0.5f, -0.588f,  //9
        0.809f, 0.5f, 0.588f,   //1
        1.0f, -0.5f, 0.0f,      //10

        1.0f, -0.5f, 0.0f,      //10
        0.809f, 0.5f, 0.588f,   //1
        0.309f, -0.5f, 0.951f,  //2

        0.309f, -0.5f, 0.951f,  //2
        0.0f, -1.118f, 0.0f,    //12
        1.0f, -0.5f, 0.0f,      //10

        -0.809f, -0.5f, 0.588f,   //4
        0.0f, -1.118f, 0.0f,    //12
        0.309f, -0.5f, 0.951f,  //2

        -0.809f, -0.5f, -0.588f,   //6
        0.0f, -1.118f, 0.0f,    //12
        -0.809f, -0.5f, 0.588f,   //4

        0.309f, -0.5f, -0.951f, //8
        0.0f, -1.118f, 0.0f,    //12
        -0.809f, -0.5f, -0.588f,   //6

        0.0f, -1.118f, 0.0f,    //12
        1.0f, -0.5f, 0.0f,      //10
        0.309f, -0.5f, -0.951f, //8
    };

    int pos = 32 * 9;

    // Вершини конуса
    for (int x = 0; x <= X_SEGMENTS; x++)
    {
        float xSegment = (float)x / (float)X_SEGMENTS;
        float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(PI / 2);
        float yPos = 0.0;//std::cos(ySegment * PI);
        float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(PI / 2);
        vertices[pos] = xPos;
        vertices[pos + 1] = yPos;
        vertices[pos + 2] = zPos;
        pos += 3;
        xSegment = (float)(x+1) / (float)X_SEGMENTS;
        xPos = std::cos(xSegment * 2.0f * PI) * std::sin(PI / 2);
        yPos = 0.0;//std::cos(ySegment * PI);
        zPos = std::sin(xSegment * 2.0f * PI) * std::sin(PI / 2);
        vertices[pos] = xPos;
        vertices[pos + 1] = yPos;
        vertices[pos + 2] = zPos;
        pos += 3;
        vertices[pos] = 0.0;
        vertices[pos + 1] = 0.0;
        vertices[pos + 2] = 0.0;
        pos += 3;
        xSegment = (float)x / (float)X_SEGMENTS;
        xPos = std::cos(xSegment * 2.0f * PI) * std::sin(PI / 2);
        yPos = 0.0;//std::cos(ySegment * PI);
        zPos = std::sin(xSegment * 2.0f * PI) * std::sin(PI / 2);
        vertices[pos] = xPos;
        vertices[pos + 1] = yPos;
        vertices[pos + 2] = zPos;
        pos += 3;
        xSegment = (float)(x + 1) / (float)X_SEGMENTS;
        xPos = std::cos(xSegment * 2.0f * PI) * std::sin(PI / 2);
        yPos = 0.0;//std::cos(ySegment * PI);
        zPos = std::sin(xSegment * 2.0f * PI) * std::sin(PI / 2);
        vertices[pos] = xPos;
        vertices[pos + 1] = yPos;
        vertices[pos + 2] = zPos;
        pos += 3;
        vertices[pos] = 0.0;
        vertices[pos + 1] = 2.0;
        vertices[pos + 2] = 0.0;
        pos += 3;
    }

    /*
    int pos = 36*3;
    for (int y = 0; y <= Y_SEGMENTS; y++)
    {
        for (int x = 0; x <= X_SEGMENTS; x++)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            vertices[pos] = xPos;
            vertices[pos+1] = yPos;
            vertices[pos+2] = zPos;
            pos += 3;
        }
    }
    */

    std::vector<float> sphereVertices;
    std::vector<int> sphereIndices;

        // Вершини сферы
        for (int y = 0; y <= Y_SEGMENTS; y++)
        {
            for (int x = 0; x <= X_SEGMENTS; x++)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                sphereVertices.push_back(xPos);
                sphereVertices.push_back(yPos);
                sphereVertices.push_back(zPos);
            }
        }

    // Индексы, генерирующие сферу
    for (int i = 0; i < Y_SEGMENTS; i++)
    {
        for (int j = 0; j < X_SEGMENTS; j++)
        {
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
            sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
            sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        }
    }

    unsigned int VBO, roomVAO;
    glGenVertexArrays(1, &roomVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(roomVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int d20VAO;
    glGenVertexArrays(1, &d20VAO);
    glBindVertexArray(d20VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int coneVAO;
    glGenVertexArrays(1, &coneVAO);
    glBindVertexArray(coneVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*
    unsigned int sphereVAO;
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    */

    unsigned int sphereVBO, sphereVAO;
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), &sphereVertices[0], GL_STATIC_DRAW);

    GLuint element_buffer_object;
    glGenBuffers(1, &element_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(int), &sphereIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader.use();
        Shader.setVec3("objectColor", 1.0f, 1.0f, 0.5f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        Shader.setMat4("projection", projection);
        Shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        Shader.setMat4("model", model);

        // Комната
        glBindVertexArray(roomVAO);
        glDrawArrays(GL_TRIANGLES, 24, 6);
        float n = 1 / 100.0;
        for (int i = 0; i < 4; i++) {
            Shader.setVec3("objectColor", 0.0f, 0.5 - n, 1.0 - n);
            n += n;
            glDrawArrays(GL_TRIANGLES, i*6, 6);
        }

        Shader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        
        glDrawArrays(GL_TRIANGLES, 30, 6);

        //Куб
        Shader.setMat4("projection", projection);
        Shader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        model = glm::scale(model, glm::vec3(0.2f)); 
        Shader.setMat4("model", model);

        //Shader.setVec3("objectColor", 1.0f, 0.5f, 0.0f);

        glBindVertexArray(cubeVAO);
        n = 1 / 100.0;
        for (int i = 0; i < 6; i++) {
            Shader.setVec3("objectColor", 1.0 - n, 0.5 - n, 0.0f);
            n += n;
            if(i % 3 == 0)n = 1 / 100.0;
            glDrawArrays(GL_TRIANGLES, i * 6, 6);
        }
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        

        //d20
        Shader.setMat4("projection", projection);
        Shader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::translate(model, d20Pos);
        model = glm::scale(model, glm::vec3(0.5f)); 
        Shader.setMat4("model", model);
        n = 1 / 20.0;
        for (int i = 0; i < 20; i++) {
            Shader.setVec3("objectColor", n*i, n*i, n*i);
            glBindVertexArray(d20VAO);
            glDrawArrays(GL_TRIANGLES, 36+i*3, 3);
        }
        //glDrawArrays(GL_TRIANGLES, 96, 300);

        //Конус
        Shader.setMat4("projection", projection);
        Shader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, conePos);
        model = glm::scale(model, glm::vec3(0.5f)); 
        Shader.setMat4("model", model);

        Shader.setVec3("objectColor", 0.0f, 1.0f, 0.33f);

        glBindVertexArray(coneVAO);
        glDrawArrays(GL_TRIANGLES, 96, 300);


        //Сфера
        Shader.setMat4("projection", projection);
        Shader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, spherePos);
        model = glm::scale(model, glm::vec3(0.5f)); 
        Shader.setMat4("model", model);
        Shader.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
        glBindVertexArray(sphereVAO);
        glDrawElements(GL_TRIANGLES, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);
        
        /*
        //Сфера

        Shader.setMat4("projection", projection);
        Shader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, spherePos);
        model = glm::scale(model, glm::vec3(0.2f)); 
        Shader.setMat4("model", model);

        Shader.setVec3("objectColor", 1.0f, 0.5f, 0.0f);

        glBindVertexArray(sphereVAO);
        glDrawArrays(GL_TRIANGLES, 36, 6000);
        */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &roomVAO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}