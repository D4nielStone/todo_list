#pragma once
#include <cmath>
#include <array>

namespace bgui_utils {
    template<size_t R, size_t C, typename T>
    class mat {
    public:
        std::array<T, R * C> m{};
        
        mat() {
            for (size_t i = 0; i < R * C; ++i)
                m[i] = T(0);
            if (R == C) { // identity if square
                for (size_t i = 0; i < R; ++i)
                    (*this)(i, i) = T(1);
            }
        }

        T& operator()(size_t row, size_t col) {
            return m[row * C + col];
        }

        const T& operator()(size_t row, size_t col) const {
            return m[row * C + col];
        }

        const T* data() const {
            return m.data();
        }

        template<size_t C2>
        mat<R, C2, T> operator*(const mat<C, C2, T>& other) const {
            mat<R, C2, T> result;
            for (size_t i = 0; i < R; ++i) {
                for (size_t j = 0; j < C2; ++j) {
                    result(i, j) = T(0);
                    for (size_t k = 0; k < C; ++k) {
                        result(i, j) += (*this)(i, k) * other(k, j);
                    }
                }
            }
            return result;
        }

        mat<R, C,T> operator*=(const mat<R, C, T>& other) {
            *this = (*this) * other;
            return *this;
        }

        mat<R, C, T> operator=(const mat<R, C, T>& other) {
            for (size_t i = 0; i < R * C; ++i)
                m[i] = other.m[i];
            return *this;
        }
        mat<R, C, T> operator*=(T scalar) {
            for (size_t i = 0; i < R * C; ++i)
                m[i] *= scalar;
            return *this;
        }
    };

    using mat4 = mat<4, 4, float>;
    using mat3 = mat<3, 3, float>;
    using mat2 = mat<2, 2, float>;

    inline void orthographic(mat4& mat, float left, float right, float bottom, float top, float near = 0.1f, float far = 20.f) {
        mat(0, 0) = 2.0f / (right - left);
        mat(1, 1) = 2.0f / (top - bottom);
        mat(2, 2) = -2.0f / (far - near);
        mat(0, 3) = -(right + left) / (right - left);
        mat(1, 3) = -(top + bottom) / (top - bottom);
        mat(2, 3) = -(far + near) / (far - near);
        mat(3, 3) = 1.0f;
    }
    inline void translate(mat4& mat, float x, float y, float z) {
        mat(0, 3) += x;
        mat(1, 3) += y;
        mat(2, 3) += z;
    }
    inline void scale(mat4& mat, float sx, float sy, float sz) {
        mat(0, 0) *= sx;
        mat(1, 1) *= sy;
        mat(2, 2) *= sz;
    }
} // namespace bgui_utils