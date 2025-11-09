#pragma once
#include "gl/shader.hpp"

namespace butil {
    class material {
    public:
        shader m_shader;
        butil::color m_bg_color;

        // border
        butil::color m_border_color;
        float m_border_radius;
        bool m_bordered;
        int m_border_size;
        bool m_visible;

        material();
        ~material();
        void bind_uniforms();

        bool operator==(const material &other) const {
            return (
                m_shader == other.m_shader &&
                m_bg_color == other.m_bg_color &&
                m_border_color == other.m_border_color &&
                m_border_radius == other.m_border_radius &&
                m_bordered == other.m_bordered &&
                m_border_size == other.m_border_size
            );
        };
    };
}