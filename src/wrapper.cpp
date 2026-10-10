#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
#include "wrapper.hpp"

// Window implementations

// Constructor
Window::Window(int width,int height, const std::string& title): width(width), height(height), title(title){

    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);

    if (!this->window){
        throw std::runtime_error("Error creating the window");
    }

}

Window::Window(Window&& other) noexcept
: width(other.width), height(other.height),
  title(std::move(other.title)), window(other.window){
    other.window = nullptr;
}

// Destructor
Window::~Window(){
    if (this->window){
        glfwDestroyWindow(this->window);
    }
}

Window& Window::operator=(Window&& other)noexcept{

    if (this != &other)
    {
        glfwDestroyWindow(window);
        this->height = other.height;
        this->width = other.width;
        this->title = std::move(other.title);
        this->window = other.window;
    
        other.window = nullptr;
    }
    return *this;
}
void Window::setFramebufferSizeCallback(GLFWframebuffersizefun func){
    glfwSetFramebufferSizeCallback(this->window, func);
}

bool Window::windowShouldClose(){
    return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}

void Window::getCursorPos(double& x, double& y){
    glfwGetCursorPos(window, &x, &y);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun func){
    glfwSetMouseButtonCallback(this->window, func);
}

void Window::setCursorPosCallback(void (*func)(GLFWwindow* window, double x, double y)){
    glfwSetCursorPosCallback(window, func);
}

// GlobalWindow implementations
WindowConfig::WindowConfig(){
    if (!glfwInit()){
        throw std::runtime_error("Error initializing the global configuration");
    }
}

WindowConfig::~WindowConfig(){
    glfwTerminate();
}

void WindowConfig::pollEvents(){
    glfwPollEvents();
}

void WindowConfig::setContext(Window& win){
    glfwMakeContextCurrent(win.window);
}

void Window::setUserPointer(void* pointer)
{
    glfwSetWindowUserPointer(window, pointer);
}