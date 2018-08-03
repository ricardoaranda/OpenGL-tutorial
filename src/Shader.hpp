//
//  Shader.hpp
//  OpenGL_3
//
//  Created by Aranda9 on 7/31/18.
//  Copyright © 2018 Ricardo Aranda. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#pragma once

#include <string>
#include <GL/glew.h>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filePath);
    ~Shader();
    
    void bind() const;
    void unbind() const;
    
    void setUnifrom4f (const std::string& name, float v0, float v1, float v2, float v3);
    GLint getUniformLocation (const std::string& name);
    
    ShaderProgramSource parseShader (const std::string& filePath);
    GLuint compileShader (unsigned int type, const std::string& source);
    GLuint createShader (const std::string& vertexShader, const std::string& fragmentShader);
private:
    std::string m_filePath;
    GLuint m_rendereID;
    // caching for uniforms
};

#endif /* Shader_hpp */
