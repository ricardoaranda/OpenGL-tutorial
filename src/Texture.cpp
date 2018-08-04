//
//  Texture.cpp
//  OpenGL_3
//
//  Created by Aranda9 on 8/1/18.
//  Copyright © 2018 Ricardo Aranda. All rights reserved.
//

#include "Texture.hpp"
#include "../src/vendor/stb_image.h"

Texture::Texture (const std::string& path)
        : m_filePath (path), m_localBuffer (nullptr),
          m_width (0), m_height (0), m_BPP (0)
{
    stbi_set_flip_vertically_on_load (1);
    m_localBuffer = stbi_load (path.c_str(), &m_width, &m_height, &m_BPP, 4);
    
    GLCall (glGenTextures (1, &m_RendereID));
    GLCall (glBindTexture (GL_TEXTURE_2D, m_RendereID));
    
    GLCall (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall (glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    GLCall  (glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    GLCall (glBindTexture (GL_TEXTURE_2D, 0));
    
    if (m_localBuffer)
        stbi_image_free (m_localBuffer);
}

Texture::~Texture()
{
    GLCall (glDeleteTextures (1, &m_RendereID));
}

void Texture::bind (GLuint slot) const
{
    GLCall (glActiveTexture (GL_TEXTURE0 + slot));
    GLCall (glBindTexture (GL_TEXTURE_2D, m_RendereID));
}

void Texture::unbind() const
{
    GLCall (glBindTexture (GL_TEXTURE_2D, 0));
}
