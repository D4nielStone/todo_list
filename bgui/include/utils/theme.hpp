#pragma once
#include "vec.hpp"

namespace butil {
    struct theme{
        butil::vec4 m_clear_color;
        butil::vec4 m_text_color;
        butil::vec4 m_hl_color;
    };
    
    static const theme light_theme = {
        {0.89f, 0.89f, 0.89f, 1.f},
        {0.f, 0.f, 0.f, 1.f},
        {0.1f, 0.1f, 0.1f, 1.f}
    };
    static const theme dark_theme = {
        {0.11f, 0.11f, 0.11f, 1.f},
        {1.f, 1.f, 1.f, 1.f},
        {0.9f, 0.9f, 0.9f, 1.f}
    };
}; // namespace butil