#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>
#include "os/os.hpp"

butil::vec2i bos::get_window_size() {
    if (glfwInit() == GLFW_TRUE) {
        GLFWwindow* window = glfwGetCurrentContext();
        if (window) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            return butil::vec2i{width, height};
        }
    }
    return butil::vec2i{800, 600};
}
std::string bos::read_file(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path + "\n");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

butil::mat4 bos::get_projection() {
    auto size = bos::get_window_size();
    auto width = size[0];
    auto height = size[1];
    return butil::orthographic(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f);
}