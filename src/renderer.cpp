#include "glad/gl.h"
#include "glFunc.hpp"
#include "renderer.hpp"
#include "elements/baseObject.hpp"
#include <GL/glext.h>
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <vector>
#include <memory>
#include "exceptions/shaderCompileError.hpp"
#include "../build/bin/generated/shaders.hpp"

// define the offset for the dataVbo
#define STRIDE_SIZE 12 * sizeof(float) + sizeof(int) + sizeof(bool)

void checkCompileError(GLuint shaderID){
    GLint success;
    
    //Consulta o status de compilação (GL_COMPILE_STATUS)
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    
    //Se o resultado for GL_FALSE, a compilação falhou
    if (success == GL_FALSE) {
        GLint logLength;
        // Descobre o tamanho da mensagem de erro
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        
        // Cria um buffer para armazenar o texto do erro
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(shaderID, logLength, &logLength, &errorLog[0]);
        
        // Lança a exceção
        throw shader_compile_error(&errorLog[0]);
    }

}

Renderer::Renderer(){}

Renderer::~Renderer(){
    glDeleteBuffers(1,&quadVbo);
    quadVbo = 0;
    glDeleteBuffers(1,&dataVbo);
    dataVbo = 0;
    glDeleteVertexArrays(1, &Vao);
    Vao = 0;
    glDeleteProgram(shaderProgram);
}

void Renderer::render(std::vector<std::unique_ptr<BaseObject>>& elements){
    if (!initComplete){
        throw std::runtime_error("Renderer initialization incomplete");
        return;
    }

    if (quadVbo == 0 || Vao== 0 || dataVbo == 0){
        throw std::runtime_error("Vertices buffer not initialized");
        return;
    }
    glClearColor(0.f,0.f,0.f,0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    
        glBindVertexArray(Vao);
    
        glDrawArraysInstanced(
            GL_TRIANGLES,
            0,
            6,
            elements.size()
        );
    
        glUseProgram(0);
}

void Renderer::init(){
    quadVbo = OpenGL::createVBO();
    dataVbo = OpenGL::createVBO();
    Vao = OpenGL::createVAO();
    glDisable(GL_CULL_FACE);
    glBindVertexArray(Vao);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, dataVbo);

    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        STRIDE_SIZE,
        (void*)0
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        STRIDE_SIZE,
        (void*)(2 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(
        3,
        4,
        GL_FLOAT,
        GL_FALSE,
        STRIDE_SIZE,
        (void*)(4 * sizeof(float))
    );
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(
        4,
        4,
        GL_FLOAT,
        GL_FALSE,
        STRIDE_SIZE,
        (void*)(8 * sizeof(float))
    );
    glEnableVertexAttribArray(4);

    glVertexAttribPointer(
        5,
        1,
        GL_FLOAT,
        GL_FALSE,
        STRIDE_SIZE,
        (void*)(12 * sizeof(float))
    );
    glEnableVertexAttribArray(5);
    
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    
    OpenGL::uploadVBO(quadVbo, quadVertices, sizeof(quadVertices));
    glBindVertexArray(0);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaders::shader_vert, NULL);
    glCompileShader(vertexShader);
    checkCompileError(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&shaders::shader_frag, NULL);
    glCompileShader(fragmentShader);
    checkCompileError(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    projectionLocation = glGetUniformLocation(shaderProgram, "projection");
    glUseProgram(shaderProgram);
    
    initComplete = true;
}

void Renderer::resize(int width, int height){
    projection = glm::ortho(
        0.0f,
        static_cast<float>(width),
        static_cast<float>(height),
        0.0f
    );
    glViewport(0,0,width,height);

    if (shaderProgram){
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(
            projectionLocation,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );
    }
}

void Renderer::load(std::vector<std::unique_ptr<BaseObject>>& elements){
    std::vector<ElementData> temp;
    temp.reserve(elements.size());
    for (auto& element : elements){
        
        auto position = element->getPosition();
        auto size = element->getSize();
        auto style = element->getStyle();
    
        temp.push_back({
            size.x,
            size.y,
            position.x,
            position.y,
            style.color.x,
            style.color.y,
            style.color.z,
            style.color.a,
            style.borderColor.x,
            style.borderColor.y,
            style.borderColor.z,
            style.borderColor.a,
            style.borderSize
        });

    }

    glBindBuffer(GL_ARRAY_BUFFER, dataVbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        temp.size() * sizeof(ElementData),
        temp.data(),
        GL_DYNAMIC_DRAW
    );
}