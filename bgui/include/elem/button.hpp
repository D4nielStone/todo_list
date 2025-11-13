#pragma once
#include "elem/text.hpp"
#include <functional>

namespace elements {
    class button : public element {
    private:
        std::function<void()> m_function;
        text m_label;
    public:
        button(const std::string& name, const float scale, const std::function<void()>& f);
        ~button();
        
        void update() override;
        void get_draw_calls(std::vector<draw_call>& calls) override;
        void set_theme(const butil::theme& t) override;
    };
} // namespace elements