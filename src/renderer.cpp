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

const char *const vertexShaderSource = R"(
    #version 330 core
    
    uniform mat4 projection;
    
    layout(location = 0) in vec2 aPos;
    layout(location = 1) in vec2 aSize;
    layout(location = 2) in vec2 aPosition;
    layout(location = 3) in vec4 aColor;
    layout(location = 4) in vec4 aBorderColor;
    layout(location = 5) in float aBorderSize;
    
    out vec4 vertexColor;
    out vec4 borderColor;
    out float borderSize;
    out vec2 localPos;
    out vec2 elementSize;
    
    void main(){
        
      vec2 aFinal = aPos * aSize + aPosition;
      
      gl_Position = projection * vec4(aFinal,0.0,1.0); 
      vertexColor = aColor;
    
      borderColor = aBorderColor;
      borderSize = aBorderSize;
      localPos = aPos;
      elementSize = aSize;
    }
)";

const char*const fragmentShaderSource = R"(
    #version 330 core
    
    in vec4 vertexColor;
    in vec4 borderColor;
    in float borderSize;
    in vec2 localPos;
    in vec2 elementSize;
    
    
    out vec4 fragColor;
    
    void main() {
        vec2 edgeDistance =
            min(localPos, vec2(1.0) - localPos) * elementSize;
    
        if (edgeDistance.x < borderSize ||
            edgeDistance.y < borderSize) {
            fragColor = vec4(borderColor.x/255.0,borderColor.y/255.0,borderColor.z/255.0,borderColor.w);
        } else {
            fragColor = vec4(vertexColor.x/255.0,vertexColor.y/255.0,vertexColor.z/255.0,vertexColor.w);
        }   
    }
)";

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
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkCompileError(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource, NULL);
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