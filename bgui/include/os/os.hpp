#pragma once
#include "utils/vec.hpp"

namespace bgui_os {
    bgui_utils::vec2i get_window_size();
    std::string read_file(const std::string& path);
} // namespace bgui_os