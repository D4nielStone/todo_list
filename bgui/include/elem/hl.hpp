#pragma once
#include "element.hpp"

namespace elements {
    class hl : public element {
    public:
        hl();
        ~hl() = default;

        void update() override;
        void set_theme(const butil::theme& t) override;
    };
} // namespace elements