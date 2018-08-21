//
//  Shader.cpp
//  OpenGL_3
//
//  Created by Aranda9 on 7/31/18.
//  Copyright © 2018 Ricardo Aranda. All rights reserved.
//

#include "Shader.hpp"
#include "Renderer.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


Shader::Shader (const std::string& filePath)
: m_filePath(filePath), m_rendereID(0)
{
    ShaderProgramSource source = parseShader (filePath);
    m_rendereID = createShader (source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    GLCall (glDeleteProgram (m_rendereID));
}

void Shader::bind() const
{
    GLCall (glUseProgram (m_rendereID));
}
void Shader::unbind() const
{
    GLCall (glUseProgram (0));
}

void Shader::setUnifrom1i (const std::string& name, int value)
{
    GLCall (glUniform1i (getUniformLocation (name), value));
}

void Shader::setUnifrom4f (const std::string& name, float v0, float v1, float v2, float v3)
{
    
    GLCall (glUniform4f (getUniformLocation (name), v0, v1, v2, v3));
}

void Shader::setUniformMatrix4fv (const std::string &name, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    GLCall (glUniformMatrix4fv (getUniformLocation (name), count, transpose, value));
}

GLint Shader::getUniformLocation (const std::string& name)
{
    GLCall (GLint location = glGetUniformLocation (m_rendereID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " does not exist." << std::endl;
    return location;
}

ShaderProgramSource Shader::parseShader (const std::string& filePath)
{
    std::ifstream stream (filePath);
    
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline (stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find ("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find ("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    
    return { ss[0].str(), ss[1].str() };
}

GLuint Shader::compileShader (unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource (id, 1, &src, nullptr);
    glCompileShader (id);
    
    /* compilation error check */
    int result;
    glGetShaderiv (id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog (id, length, &length, message);
        
        std::cout << "Failed to compile " <<
        (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << " shader" << std::endl;
        std::cout << message << std::endl;
        
        glDeleteShader (id);
        return 0;
    }
    
    return id;
}

GLuint Shader::createShader (const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader (GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader (GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader (program, vs);
    glAttachShader (program, fs);
    glLinkProgram (program);
    glValidateProgram (program);
    
    glDeleteShader (vs);
    glDeleteShader (fs);
    
    return program;
}
