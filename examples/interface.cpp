#include "glad/gl.h"
#include "wrapper.hpp"
#include <iostream>
#include "glFunc.hpp"

void framebuffer_change(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "\r" << "Largura: " << width << ' '
        << "Altura: " << height << " ";
}

const char* vertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec2 aPos;

    void main()
    {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

int main()
{
    WindowConfig global;

    Window janela(800,500, std::string("Ola"));

    global.setContext(janela);

    float vertices[]= {
        // triângulo 1
            -0.5f,  0.5f,  // superior esquerdo
             0.5f,  0.5f,  // superior direito
             0.5f, -0.5f,  // inferior direito

            // triângulo 2
            -0.5f,  0.5f,  // superior esquerdo
             0.5f, -0.5f,  // inferior direito
            -0.5f, -0.5f   // inferior esquerdo
    };

    GLuint VBO = OpenGL::createVBO();
    OpenGL::uploadVBO(VBO, &vertices, sizeof(vertices));
    
    GLuint VAO = OpenGL::createVAO();

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
    
    GLuint vertexShader = OpenGL::createVertexShader(vertexShaderSource, 1);

    GLuint fragmentShader = OpenGL::createFragmentShader(fragmentShaderSource, 1);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    janela.setFramebufferSizeCallback(framebuffer_change);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!janela.windowShouldClose()){
        global.pollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        janela.swapBuffers();
    }
    return 0;
}