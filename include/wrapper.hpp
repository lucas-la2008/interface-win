#ifndef GLFW_WRAPPER__
#define GLFW_WRAPPER__

#include <GLFW/glfw3.h>
#include <string>

class WindowConfig;

class Window{
    int width = 0;
    int height = 0;
    std::string title;
    GLFWwindow* window = 0;
    friend WindowConfig;
public:

    // Constructor
    Window(int width,int height, const std::string& title);

    // Destructor
    ~Window();

    // Prevent initialization from another Window
    // e.g.
    //
    // Window b(200,200,"title");
    // Window a = b;
    Window(const Window&) = delete;

    // Prevent assignment from another Window
    // e.g.
    //
    // Window a(200,200,"title");
    // Window b;
    // b = a;
    Window& operator =(const Window&) = delete;

    // Allows move operations in initialization
    // e.g.
    //
    // Window b(200,200,"title");
    // Window a = std::move(b);
    Window(Window&& other) noexcept;

    // Allow move assignments from another Window
    // e.g.
    //
    // Window a(200,200,"title");
    // Window b;
    // b = a;
    Window& operator=(Window&& other) noexcept;

    void setFramebufferSizeCallback(GLFWframebuffersizefun func);

    bool windowShouldClose();

    void swapBuffers();

    void setUserPointer(void* pointer);

    void getCursorPos(double& x, double& y);

    void setMouseButtonCallback(void (*func)(GLFWwindow* window, int button, int action, int mods));

    void setCursorPosCallback(void (*func)(GLFWwindow* window, double x, double y));
};

class WindowConfig{

public:
    WindowConfig();

    ~WindowConfig();

    WindowConfig(const WindowConfig&) = delete;
    WindowConfig& operator=(const WindowConfig&) = delete;
    
    WindowConfig(WindowConfig&&) = delete;
    WindowConfig& operator=(WindowConfig&&) = delete;
    
    void pollEvents();

    void setContext(Window&);
};

#endif