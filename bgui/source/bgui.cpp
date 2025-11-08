#include "bgui.hpp"
#include <os/os.hpp>
#include <utils/vec.hpp>

bgui::bgui(theme gui_theme)
    : m_theme(gui_theme), m_clear_color({0.0f, 0.0f, 0.0f, 1.0f}) {
    set_theme(gui_theme);
}

bgui::~bgui() {
}

bgui_utils::mat4 bgui::get_projection() {
    bgui_utils::mat4 proj;
    auto size = bgui_os::get_window_size();
    auto width = size[0];
    auto height = size[1];
    bgui_utils::orthographic(proj, 0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
    return proj;
}

void bgui::set_theme(theme gui_theme) {
    // set the theme and update clear color accordingly
    m_theme = gui_theme;
    if (m_theme == theme::dark) {
        m_clear_color = bgui_utils::color({0.1f, 0.1f, 0.1f, 1.0f});
    } else  if (m_theme == theme::light) {
        m_clear_color = bgui_utils::color({0.9f, 0.9f, 0.9f, 1.0f});
    }
}

theme bgui::get_theme() const {
    return m_theme;
}

void bgui::clear() const {
    glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[4]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void bgui::update(layout &lay) {
    lay.update();
}

void bgui::render(layout &lay) {
    lay.draw();
    for (const auto& elem : lay.get_elements()) {
        elem->draw();
    }
}
