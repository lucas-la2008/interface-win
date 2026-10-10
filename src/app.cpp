#include "glad/gl.h"
#include "app.hpp"
#include "wrapper.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>

void App::sizeCallback(GLFWwindow* window, int width, int height){
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    app->onResize(width, height);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods){
    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (!app){ return; }


    double virtualMouseX = 
        (mouseX / static_cast<double>(width)) * static_cast<double>(app->windowX); 

    
    double virtualMouseY = 
        (mouseY / static_cast<double>(height)) * static_cast<double>(app->windowY);
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        for (auto& data : app->childrenElements){
            auto position = data->getPosition();
            auto size = data->getSize();
            
            if (virtualMouseX >= position.x && virtualMouseX <= position.x + size.x
                && virtualMouseY >= position.y && virtualMouseY <= position.y + size.y)
            {
                data->clicked();
                break;
            }
        }
    }
}

App::App(int width, int height, std::string title)
: global(), mainWindow(width,height,title), loader(), windowX(width), windowY(height){
    global.setContext(mainWindow);
    
    if(!gladLoadGL(glfwGetProcAddress)){
        throw std::runtime_error("Error at loading OpenGL");
    }

    mainWindow.setUserPointer(this);
    
    mainWindow.setFramebufferSizeCallback(App::sizeCallback);
    mainWindow.setMouseButtonCallback(mouseCallback);
    loader.init();
    loader.resize(width, height);
}

void App::run(){
    
    while(!mainWindow.windowShouldClose()){
        
        global.pollEvents();
        loader.load(childrenElements);
        
        render();
        mainWindow.swapBuffers();
    }
}

inline void App::render(){
    loader.render(childrenElements);
}

void App::onResize(int width, int height)
{
    this->windowX = static_cast<float>(width);
    this->windowY = static_cast<float>(height);
    loader.resize(width, height);
}