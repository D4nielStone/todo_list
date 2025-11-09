#pragma once
#include <glad/glad.h>
#include <os/os.hpp>
#include "utils/mat.hpp"
#include "utils/vec.hpp"

class shader {
private:
    GLuint m_id{0};
    bool m_should_delete{false};
    public:
    shader() = default;
    shader(const char* vertex_path, const char* fragment_path);
    ~shader();
    void bind();
    void unbind();

    void compile(const char* vertex_path, const char* fragment_path);
    static GLuint compile(GLenum type, const std::string& source);
    static GLuint link(GLuint vert, GLuint frag);

    void set_mat4(const char* name, const butil::mat4 matrix);
    void set_vec4(const char* name, const butil::vec4& vector);
    void set_vec3(const char* name, const butil::vec3& vector);
    void set_vec2(const char* name, const butil::vec2& vector);
    void set_bool(const char* name, const bool& v);
    void set_int(const char* name, const int& v);
    void set_float(const char* name, const float& v);

    bool operator==(const shader& other) const {
        return m_id == other.m_id;
    }
};