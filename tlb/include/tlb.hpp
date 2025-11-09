#pragma once // precautionary measure
             // set the code of each color
#define bred         "\033[0;31m"
#define bgreen       "\033[0;32m"
#define bblue        "\033[0;34m"
#define breset       "\033[0;0m"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
// \brief TLB is the main class. Todo List Bubble
class TLB {
private:
    static GLFWwindow* m_window;
public:
    TLB() = default;
    ~TLB() = default;
    static TLB& instance() {
        static TLB instance;
        return instance;
    }
    void config_layout();
    void init_graphics();
    void window_loop();
    static void error(const std::string&);
    static void info(const std::string&);
};