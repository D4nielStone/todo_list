#include "utils/material.hpp"
#include "bgui.hpp"

butil::material::material() : m_bg_color({0.05f, 0.05f, 0.05f, 0.05f}), m_border_color({0.07f, 0.07f, 0.07f, 0.07f}),
 m_border_radius(0.25f), m_border_size(20), m_bordered(true), m_visible(true) {
    bgui::instance().add_gl_call([&](){
        m_shader.compile("quad.vs", "quad.fs");
    });
}
butil::material::~material() {
}

void butil::material::bind_uniforms() {
    m_shader.bind();
    m_shader.set_vec4("u_bg_color", m_bg_color);
    m_shader.set_vec4("u_border_color", m_border_color);
    m_shader.set_bool("u_bordered", m_bordered);
    m_shader.set_float("u_border_radius", m_border_radius);
    m_shader.set_int("u_border_size", m_border_size);
    m_shader.set_int("u_visible", m_visible);
}
