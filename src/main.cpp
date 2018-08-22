#define GLEW_STATIC
#include "GL/glew.h"

#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "../src/vendor/glm/glm.hpp"
#include "../src/vendor/glm/gtc/matrix_transform.hpp"
#include "../src/vendor/glm/gtc/type_ptr.hpp"


#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

// *******************************************************************
void processInput (GLFWwindow *window);

// *******************************************************************
int main(void)
{
    srand (time(NULL));
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 777, "OpenGL Tutorial", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    glm::vec3 cubePositions[] = {
        glm::vec3 ( 0.0f,  0.0f,  0.0f),
        glm::vec3 ( 2.0f,  5.0f, -15.0f),
        glm::vec3 (-1.5f, -2.2f, -2.5f),
        glm::vec3 (-3.8f, -2.0f, -12.3f),
        glm::vec3 ( 2.4f, -0.4f, -3.5f),
        glm::vec3 (-1.7f,  3.0f, -7.5f),
        glm::vec3 ( 1.3f, -2.0f, -2.5f),
        glm::vec3 ( 1.5f,  2.0f, -2.5f),
        glm::vec3 ( 1.5f,  0.2f, -1.5f),
        glm::vec3 (-1.3f,  1.0f, -1.5f)
    };
    
    GLuint vao;
    GLCall (glGenVertexArrays (1, &vao));
    GLCall (glBindVertexArray (vao));
    
    GLuint vbo;
    GLCall (glGenBuffers (1, &vbo));
    GLCall (glBindBuffer (GL_ARRAY_BUFFER, vbo));
    GLCall (glBufferData (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    
    Shader shader ("basic.shader");
    shader.bind();
    
    Texture texture("textures/m78.jpg");
    texture.bind();
    shader.setUnifrom1i ("u_Texture", 0);

    
    GLCall (glEnableVertexAttribArray (0));
    GLCall (glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));
    
    GLCall (glEnableVertexAttribArray (1));
    GLCall (glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3)));
    
    GLCall (glEnable (GL_DEPTH_TEST));
    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput (window);
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::vec3 cameraPos = glm::vec3 (0.0f, 0.0f, 0.3f);
        
        glm::vec3 cameraTarget = glm::vec3 (0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        
        glm::mat4 view = glm::mat4 (1.0f);
        view = glm::translate (view, glm::vec3 (0.0f, 0.0f, -3.0f));
        
        glm::mat4 projection = glm::mat4 (1.0f);
        projection = glm::perspective<float>(glm::radians(45.0f), 800 / 777, 0.1f, 100.0f);
        
        shader.setUniformMatrix4fv ("view", 1, GL_FALSE, glm::value_ptr (view));
        shader.setUniformMatrix4fv ("projection", 1, GL_FALSE, glm::value_ptr (projection));
        
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4 (1.0f);
            model = glm::translate (model, cubePositions[i]);
            
            float angle = 20.0f * i;
            if (i % 3 == 0)
                model = glm::rotate (model, (float)glfwGetTime(), glm::vec3 (0.664446f, 0.34273f, 0.261933f));
            else
                model = glm::rotate (model, glm::radians(angle), glm::vec3 (1.0f, 0.3f, 0.5f));
            
            shader.setUniformMatrix4fv ("model", 1, GL_FALSE, glm::value_ptr (model));
            
            GLCall (glDrawArrays (GL_TRIANGLES, 0, 36));
        }
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    GLCall (glDeleteBuffers (1, &vbo));
    GLCall (glDeleteVertexArrays (1, &vao));
    
    glfwTerminate();
    return 0;
}

void processInput (GLFWwindow *window)
{
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose (window, true);
    }
}
