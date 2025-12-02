#pragma once
#include "utils/draw.hpp"
// That file give me too much work, so I prefer to keep it simple

namespace bgui {
    void opengl3_render(bgui::draw_data*);
    void opengl3_clear_texture_cache();
    void set_up_opengl3();
    void shutdown_opengl3();
    GLuint get_quad_vao();
    GLuint opengl3_get_texture(const bgui::texture& tex);
} // namespace bgui