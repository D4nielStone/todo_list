#pragma once
#include <glad/glad.h>
#include <os/os.hpp>
#include "utils/mat.hpp"
#include "utils/vec.hpp"

class shader {
private:
    GLuint m_id{0};
    public:
    shader() = default;
    shader(const char* vertex_path, const char* fragment_path);
    ~shader();
    void bind();
    void unbind();

    static GLuint compile(GLenum type, const std::string& source);
    static GLuint link(GLuint vert, GLuint frag);

    void set_mat4(const char* name, const bgui_utils::mat4& matrix);
    void set_vec4(const char* name, const bgui_utils::vec4& vector);
    void set_vec3(const char* name, const bgui_utils::vec3& vector);
    void set_vec2(const char* name, const bgui_utils::vec2& vector);
};