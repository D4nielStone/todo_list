#pragma once
#include "string"
#include "utils/vec.hpp"
#include "utils/mat.hpp"

namespace bgui_os {
    bgui_utils::vec2i get_window_size();
    std::string read_file(const std::string& path);
    static bgui_utils::mat4 get_projection();
} // namespace bgui_os