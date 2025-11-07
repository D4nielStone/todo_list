#include "bgui.hpp"

bgui::bgui(theme gui_theme)
    : m_theme(gui_theme), m_clear_color(0.0f, 0.0f, 0.0f, 1.0f) {
    if (m_theme == theme::dark) {
        m_clear_color = color(0.1f, 0.1f, 0.1f, 1.0f);
    } else {
        m_clear_color = color(0.9f, 0.9f, 0.9f, 1.0f);
    }
}

bgui::~bgui() {
}

void bgui::set_theme(theme gui_theme) {
    // set the theme and update clear color accordingly
    m_theme = gui_theme;
    if (m_theme == theme::dark) {
        m_clear_color = color(0.1f, 0.1f, 0.1f, 1.0f);
    } else {
        m_clear_color = color(0.9f, 0.9f, 0.9f, 1.0f);
    }
}

theme bgui::get_theme() const {
    return m_theme;
}

void bgui::clear() const {
    glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void bgui::updateTree() {
}

void bgui::render() {
}
