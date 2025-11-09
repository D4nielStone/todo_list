#pragma once
#include "string"
#include "utils/vec.hpp"
#include "utils/mat.hpp"

namespace bos {
    butil::vec2i get_window_size();
    std::string read_file(const std::string& path);
    butil::mat4 get_projection();
} // namespace bos