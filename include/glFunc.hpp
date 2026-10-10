#ifndef GLFUNC__
#define GLFUNC__

#include "glad/gl.h"
#include <cstddef>

namespace OpenGL{
    GLuint createVBO();

    void uploadVBO(GLuint VBO,const void* data, std::size_t size);
    
    GLuint createVAO();
    
    GLuint createVertexShader(const char*& source, std::size_t count);
    
    GLuint createFragmentShader(const char*& source, std::size_t count);
}

#endif