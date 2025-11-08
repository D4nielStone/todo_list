// \brief The element is the base class for all GUI parts.

#pragma once
#include <vector>
#include <memory>
#include "gl/shader.hpp"

// \brief A draw call structure containing the necessary information to render an element.
struct draw_call {
    shader m_shader;
    GLuint m_vao{0};
    GLenum m_mode{GL_TRIANGLES};
    int m_count{6};
    bgui_utils::vec4 m_bounds{0.0f, 0.0f, 20.0f, 20.0f};

    bool operator==(const draw_call& other) const {
        return m_shader == other.m_shader &&
               m_vao == other.m_vao &&
               m_mode == other.m_mode &&
               m_count == other.m_count;
    }
};

class element {
protected:
    shader m_shader;
    // absolute position and size
    int m_x{0};
    int m_y{0};
    int m_width{0};
    int m_height{0};
public:
    element() = default;
    virtual ~element() = default;
    // \brief setters
    void set_position(int x, int y);
    void set_size(int width, int height);
    void set_x(int x);
    void set_y(int y);
    void set_rect(int x, int y, int width, int height);
    void set_shader(const shader& shd);
    // \brief getters
    int get_x() const;
    int get_y() const;
    int get_width() const;
    int get_height() const;
    shader& get_shader();

    virtual void update() = 0;
    virtual void get_draw_calls(std::vector<draw_call>& calls) = 0;
};