#include "elem/layout.hpp"
#include "bgui.hpp"

layout::layout() : m_orientation(orientation::horizontal), m_alignment(alignment::start), m_spacing_elements(1) {
        m_material.m_visible = false;
        
        set_theme(bgui::instance().get_theme());
        bgui::instance().add_gl_call([&](){
            m_material.m_shader.compile("quad.vs", "quad.fs");
        });
    };

void layout::update() {
    auto m = bos::get_mouse_position();
    float mx = m[0];
    float my = m[1];

    for (size_t i = m_elements.size(); i-- > 0; ) {
        auto elem = m_elements[i].get();

        float x = elem->get_x();
        float y = elem->get_y();
        float w = elem->get_width();
        float h = elem->get_height();

        bool inside =
            mx >= x &&
            mx <= x + w &&
            my >= y &&
            my <= y + h;

        if (inside) {
            elem->on_mouse_hover();
            // calculate click
            if(bos::get_pressed(bos::input_key::mouse_left)) {
                elem->on_pressed();
            }
            break;
        }
    }
}