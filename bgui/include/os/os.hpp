#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include "string"
#include "utils/vec.hpp"
#include "utils/mat.hpp"

namespace bos {
    enum class input_key {
        none,
        mouse_left,
        mouse_right,
        mouse_middle
    };
    enum class input_action {
        none,
        press,
        release,
        repeat
    };
    static std::unordered_map<int, input_key> s_glfw_key_reverse_map = {
        {GLFW_MOUSE_BUTTON_LEFT, input_key::mouse_left},
        {GLFW_MOUSE_BUTTON_RIGHT, input_key::mouse_right},
        {GLFW_MOUSE_BUTTON_MIDDLE, input_key::mouse_middle}
    };
    static std::unordered_map<int, input_action> s_glfw_action_reverse_map = {
        {GLFW_PRESS, input_action::press},
        {GLFW_RELEASE, input_action::release},
        {GLFW_REPEAT, input_action::repeat}
    };
    static std::unordered_map<input_key, input_action> s_input_map;

    void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    butil::vec2i get_window_size();
    butil::vec2i get_mouse_position();
    std::string read_file(const std::string& path);
    butil::mat4 get_projection();
    bool get_pressed(const input_key&);
} // namespace bos