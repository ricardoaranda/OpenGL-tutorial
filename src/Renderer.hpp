//
//  Renderer.hpp
//  OpenGL_2
//
//  Created by Aranda9 on 7/24/18.
//  Copyright © 2018 Aranda9. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __builtin_trap();
#define GLCall(f) GLClearError();\
f;\
ASSERT(GLLogCall(#f, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char * function, const char * file, int line);


#endif /* Renderer_hpp */
