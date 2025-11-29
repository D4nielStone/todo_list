#pragma once
#include "utils/draw.hpp"

namespace bkend {
    void opengl3_render(butil::draw_data*);
    void opengl3_clear_texture_cache();
    void set_up_opengl3();
    void shutdown_opengl3();
    GLuint get_quad_vao();
    GLuint opengl3_get_texture(const butil::texture& tex);
} // namespace bkend