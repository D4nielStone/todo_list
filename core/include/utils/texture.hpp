#pragma once
#include <string>
#include "vec.hpp"

namespace butil {
    struct texture {
        std::string m_path;
        butil::vec2 m_size = {0,0};

        bool operator==(const texture& other) const {
            return (m_path == other.m_path && m_size == other.m_size);
        }
    };
}