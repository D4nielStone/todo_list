#include "elements/absolute_layout.hpp"
#include "bgui.hpp"

void absolute_layout::get_draw_calls(std::vector<draw_call>& calls) {
    calls.push_back({m_shader, bgui::instance().get_quad_vao(), GL_TRIANGLES, 6});
    for (auto& elem : m_elements) {
        elem->get_draw_calls(calls);
    }
};