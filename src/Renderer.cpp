//
//  Renderer.cpp
//  OpenGL_2
//
//  Created by Aranda9 on 7/24/18.
//  Copyright © 2018 Aranda9. All rights reserved.
//

#include "Renderer.hpp"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char * function, const char * file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL error] (" << error << "): " <<
        function << " "  << file << ": " << line << std::endl;
        return false;
    }
    return true;
}
