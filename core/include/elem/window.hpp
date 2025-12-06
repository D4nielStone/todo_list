#pragma once
#include "lay/linear.hpp"
#include <string>

namespace bgui {
    class window : public linear {
    private:
        text* m_title;
        linear* m_header;
    public:
        window(const std::string& title = "");
        void set_title(const std::string& title) { m_title->set_buffer(title); }
        text& get_title() { return *m_title; }
    };
}// namespace bgui