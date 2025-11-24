
#include "elem/linear_layout.hpp"
#include "bgui.hpp"

using namespace butil;
    
linear_layout::linear_layout(const orientation& ori) {
    m_orientation = ori;
    m_material.m_visible = false;
    m_material.m_shader.compile("quad.vs", "quad.fs");
}

void linear_layout::update() {
    // no children -> nothing to do
    if (m_elements.empty()) return;

    const bool vertical = (m_orientation == orientation::vertical);
    layout::update();

    // compute total main-axis size (sum of widths or heights) + spacing between items
    int spacing = vertical ? m_spacing_elements[1] : m_spacing_elements[0]; 
    int elem_total_main = 0;

    // avaliable size subtracting my padding
    int available_main = get_size()[vertical ? 1 : 0] - m_padding[vertical ? 1 : 0] * 2;

    for (auto& elem : m_elements) {
    if (vertical)
        elem_total_main += elem->get_height() + elem->get_extern_spacing()[1];
    else
        elem_total_main += elem->get_width() + elem->get_extern_spacing()[0];
    }

    if (m_elements.size() > 1) elem_total_main += spacing * (int(m_elements.size()) - 1);

    // compute starting cursor on the main axis depending on alignment (start/center/end)
    int cursor_main;
    if (m_alignment == alignment::start)
        cursor_main = m_padding[vertical ? 1 : 0]; // in start just add my padding
    else if (m_alignment == alignment::center)
        cursor_main = (available_main - elem_total_main) / 2 + m_padding[vertical ? 1 : 0];
    else // > end
        cursor_main = available_main - elem_total_main - m_padding[vertical ? 1 : 0];

    // Place each child using cursor_main and cross-axis alignment
    for (auto& elem : m_elements) {
        // child already updated above
        int ex = 0;
        int ey = 0;

        // cross-axis (horizontal) alignment for this child
        if (m_cross_alignment == alignment::start ||
            m_cross_alignment == alignment::stretch)
            ex = m_padding[vertical ? 0 : 1];
        else if (m_cross_alignment == alignment::center)
            ex = (get_size()[vertical ? 0 : 1]- elem->get_size()[vertical ? 0 : 1]) / 2;
        else // end
            ex = get_size()[vertical ? 0 : 1] - elem->get_size()[vertical ? 0 : 1] - m_padding[vertical ? 0 : 1];

        // main-axis position = cursor_main (y)
        ey = cursor_main;

        // commit positions
        elem->set_x(ex);
        elem->set_y(ey);

        // cross stretch
        if (m_cross_alignment == alignment::stretch)
            if(vertical) elem->set_width(get_width() - m_padding[vertical ? 1 : 0]*2);
            else elem->set_height(get_height() - m_padding[vertical ? 1 : 0]*2);

        // advance cursor
        cursor_main += elem->get_size()[vertical ? 1 : 0] + elem->get_extern_spacing()[vertical ? 1 : 0];
    }
}
void linear_layout::fit_to_content() {
    const bool vertical = (m_orientation == orientation::vertical);
    int max_cross = 0;
    for (auto& elem : m_elements) {
        int cross = vertical ? elem->get_width() : elem->get_height();
        if (cross > max_cross)
            max_cross = cross;
    }
    int max_main = m_padding[vertical ? 1 : 0]*2;
    for (auto& elem : m_elements) {
        max_main += vertical ? elem->get_height() : elem->get_width();
        max_main += elem->get_extern_spacing()[vertical ? 1 : 0]*2;
    }

    if (vertical) {
        set_width(max_cross + m_padding[0]*2);
        set_height(max_main);
    } else {
        set_height(max_cross + m_padding[1]*2);
        set_width(max_main);
    }
}
