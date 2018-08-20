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

// *******************************************************************
void processInput (GLFWwindow *window);

// *******************************************************************
int main(void)
{
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
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,    // generic vertex attribute (x, y, r, b, g)
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,     // another generic vertex attribute
         0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    
    
    GLuint vao;
    GLCall (glGenVertexArrays (1, &vao));
    GLCall (glBindVertexArray (vao));
    
    GLuint vbo;
    GLCall (glGenBuffers (1, &vbo));
    GLCall (glBindBuffer (GL_ARRAY_BUFFER, vbo));
    GLCall (glBufferData (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    
    GLuint ebo;
    GLCall (glGenBuffers (1, &ebo));
    GLCall (glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ebo));
    GLCall (glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW));
    
    Shader shader ("basic.shader");
    shader.bind();
    
    Texture texture("textures/m78.jpg");
    texture.bind();
    shader.setUnifrom1i ("u_Texture", 0);
    
    GLCall (glEnableVertexAttribArray (0)); // attrib location position as arguemtn
    GLCall (glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0));

    GLCall (glEnableVertexAttribArray (1)); // attrib location color as argument
    GLCall (glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE,
                                   sizeof(float) * 7, (void*)(sizeof(float) * 2)));
    
    GLCall (glEnableVertexAttribArray (2));
    GLCall (glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE,
                                   sizeof(float) * 7, (void*)(sizeof(float) * 5)));
    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput (window);
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        GLCall (glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
        
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
