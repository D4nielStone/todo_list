#include <iostream>
#include "tlb.hpp"
#include "bgui.hpp"

GLFWwindow* TLB::m_window = nullptr;

void TLB::error(const std::string& msg) {
    throw std::runtime_error(msg);
}
void TLB::info(const std::string& msg) {
    std::cout << breset << "TLB::" << bgreen << msg << "\n" << breset;
}
void TLB::initGraphics() {
    TLB::info("Creating new window...");
    // step 1: init glfw
    if (!glfwInit()) {
        TLB::error("Glfw initialization");
    }
    // step 2: create window and init glad
    m_window = glfwCreateWindow(500, 700, "TLB::Todo List Bubble Application", NULL, NULL);
    if (!m_window) {
        TLB::error("Invalid window");
    };

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        TLB::error("Glad initialization");
    }
    TLB::info("Window created");
}
void TLB::windowLoop() {
    TLB::info("Starting main loop");
    while(!glfwWindowShouldClose(m_window)) {
        // poll events
        glfwPollEvents();

        // --- //
        // rendering
        bgui::instance().clear();
        bgui::instance().update(m_main_layout);
        bgui::instance().render(m_main_layout);
        // --- //

        // swap buffers
        glfwSwapBuffers(m_window);
    }
}