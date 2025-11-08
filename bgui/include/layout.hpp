#pragma once
#include "element.hpp"
#include <algorithm>

class layout : public element {
private:
    std::vector<std::unique_ptr<element>> m_elements;
public:
    layout() = default;
    ~layout() = default;
    template<typename T, typename... Args>
    T& add_element(Args&&... args) {
        auto elem = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *elem;
        m_elements.push_back(std::move(elem));
        return ref;
    }
    const std::vector<std::unique_ptr<element>>& get_elements() const {
        return m_elements;
    }
    bool remove_element(element* elem) {
        auto it = std::remove_if(m_elements.begin(), m_elements.end(),
            [elem](const std::unique_ptr<element>& e) { return e.get() == elem; });
        if (it != m_elements.end()) {
            m_elements.erase(it, m_elements.end());
            return true;
        }
        return false;
    }
};

class absolute_layout : public layout {
public:
    absolute_layout() = default;
    ~absolute_layout() = default;

    void draw() override {
        for (const auto& elem : get_elements()) {
            elem->draw();
        }
    }
    void update() override {
        for (const auto& elem : get_elements()) {
            elem->update();
        }
    }
};