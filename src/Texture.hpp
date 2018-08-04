//
//  Texture.hpp
//  OpenGL_3
//
//  Created by Aranda9 on 8/1/18.
//  Copyright © 2018 Ricardo Aranda. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <string>
#include "Renderer.hpp"
#pragma once

class Texture
{
public:
    Texture (const std::string& path);
    ~Texture();
    
    void bind (GLuint slot = 0) const;
    void unbind() const;
    
    inline int getWidth() const { return m_width; };
    inline int getHeight() const { return m_height; };
private:
    GLuint m_RendereID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_BPP;
};

#endif /* Texture_hpp */
